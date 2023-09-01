using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;

namespace MessageBusWebAPI.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class SomeController : ControllerBase
    {
        [HttpPost]
        public SomeAnotherData Post([FromBody] SomeData someData)
        {
            return new SomeAnotherData 
            { 
                Id = 47, 
                Names = new List<string?> { "abc", null, "ffff", "ok" } 
            };
        }
    }
}
