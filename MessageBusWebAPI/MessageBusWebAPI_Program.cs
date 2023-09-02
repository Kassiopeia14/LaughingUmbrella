using Microsoft.AspNetCore.Server.Kestrel.Core;
using Microsoft.AspNetCore.Server.Kestrel.Https;
using modSelfSignedIssuer;
using modWorldLog;
using System.Security.Authentication;
using System.Security.Cryptography.X509Certificates;

var builder = WebApplication.CreateBuilder(args);

string password = SelfSignedIssuer.GeneratePassword(8);
byte[] certificateBytes = SelfSignedIssuer.Issue("Self-Signed", TimeSpan.FromDays(10000), password);

X509Certificate2 sslCertificate = new X509Certificate2(certificateBytes, password);

builder.WebHost.ConfigureKestrel(serverOptions =>
{
    serverOptions.ListenAnyIP(8000, listenOptions =>
    {
        var connectionOptions = new HttpsConnectionAdapterOptions();
        connectionOptions.SslProtocols = SslProtocols.Tls12;
        connectionOptions.ServerCertificate = sslCertificate;
        listenOptions.UseHttps(connectionOptions);
    });
});

builder.Services.AddSingleton<IWorldLog, WorldLog>();

builder.Services.AddControllers();

var app = builder.Build();

// Configure the HTTP request pipeline.

app.UseAuthorization();

app.MapControllers();

app.Run();
