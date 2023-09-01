﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json.Serialization;
using System.Threading.Tasks;

namespace modWorldLog
{
    public class WorldInitialState
    {
        [JsonPropertyName("apple")]
        public Apple Apple { get; set; }

        [JsonPropertyName("pit")]
        public Pit Pit { get; set; }
    }
}