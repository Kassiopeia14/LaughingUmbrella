using System.Security.Cryptography.X509Certificates;
using System.Security.Cryptography;
using System.Text;

namespace modSelfSignedIssuer
{
    public static class SelfSignedIssuer
    {
        public static byte[] Issue(
            string subjectName, 
            TimeSpan lifeTime,
            string exportPassword) 
        {
            RSA rsaKey = RSA.Create(2048);
            string subject = "CN=" + subjectName;
            CertificateRequest certificateRequest = new CertificateRequest(subject, rsaKey, HashAlgorithmName.SHA256, RSASignaturePadding.Pkcs1);
            certificateRequest.CertificateExtensions.Add(new X509BasicConstraintsExtension(true, false, 0, true));
            certificateRequest.CertificateExtensions.Add(new X509SubjectKeyIdentifierExtension(certificateRequest.PublicKey, false));
            var expire = DateTimeOffset.Now.Add(lifeTime);
            X509Certificate2 certificate = certificateRequest.CreateSelfSigned(DateTimeOffset.Now, expire);

            byte[] certificateBytes = certificate.Export(X509ContentType.Pfx, exportPassword);
            return certificateBytes;
        }

        public static string GeneratePassword(int length)
        {
            const string valid = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
            StringBuilder res = new StringBuilder();
            Random random = new Random();

            while (0 < length--)
            {
                res.Append(valid[random.Next(valid.Length)]);
            }
            return res.ToString();
        }
    }
}