using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json.Serialization;
using System.Threading.Tasks;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace modWorldLog
{
    public class AgentState
    {
        [JsonPropertyName("x")]
        public int X { get; set; }

        [JsonPropertyName("y")]
        public int Y { get; set; }

        [JsonPropertyName("accumulated_reward")]
        public double AccumulatedReward { get; set; }

        [JsonPropertyName("q_function")]
        public QFunction QFunction { get; set; }
    }
}
