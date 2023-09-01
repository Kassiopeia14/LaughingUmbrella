using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json.Serialization;
using System.Threading.Tasks;

namespace modWorldLog
{
    public class Epoch
    {
        [JsonPropertyName("number")]
        public int Number { get; set; }

        [JsonPropertyName("agent_states")]
        public List<AgentState> AgentStates { get; set; }
    }
}
