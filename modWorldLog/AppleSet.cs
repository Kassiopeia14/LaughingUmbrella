using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json.Serialization;
using System.Threading.Tasks;

namespace modWorldLog
{
    public class AppleSet
    {
        [JsonPropertyName("cells")]
        public List<AppleCell> AppleCells { get; set; }
    }
}
