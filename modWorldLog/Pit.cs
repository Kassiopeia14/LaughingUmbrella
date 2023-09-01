using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json.Serialization;
using System.Threading.Tasks;

namespace modWorldLog
{
    public class Pit
    {
        [JsonPropertyName("cells")]
        public List<PitCell> PitCells { get; set; }
    }
}
