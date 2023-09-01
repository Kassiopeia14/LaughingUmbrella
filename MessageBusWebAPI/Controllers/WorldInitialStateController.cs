using Microsoft.AspNetCore.Mvc;
using modWorldLog;
using System.Runtime.CompilerServices;

// For more information on enabling Web API for empty projects, visit https://go.microsoft.com/fwlink/?LinkID=397860

namespace MessageBusWebAPI.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class WorldInitialStateController : ControllerBase
    {
        IWorldLog worldLog;

        public WorldInitialStateController(IWorldLog _worldLog)
        {
            worldLog = _worldLog;
        }

        [HttpGet]
        public WorldInitialState Get()
        {
            return worldLog.getWorldInitialState();
        }

        [HttpPost]
        public string Post([FromBody] WorldInitialState worldInitialState)
        {
            worldLog.setWorldInitialState(worldInitialState);

            return "ok";
        }
    }
}
