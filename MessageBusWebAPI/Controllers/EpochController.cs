using Microsoft.AspNetCore.Mvc;
using modWorldLog;

// For more information on enabling Web API for empty projects, visit https://go.microsoft.com/fwlink/?LinkID=397860

namespace MessageBusWebAPI.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class EpochController : ControllerBase
    {
        IWorldLog worldLog;

        public EpochController(IWorldLog _worldLog)
        {
            worldLog = _worldLog;
        }

        [HttpGet("{epochNumber}")]
        public Epoch Get(int epochNumber)
        {
            return worldLog.getEpoch(epochNumber);
        }

        [HttpPost]
        public string Post([FromBody] Epoch epoch)
        {
            worldLog.setEpoch(epoch);

            return "epoch " + epoch.Number + " set";
        }
    }
}
