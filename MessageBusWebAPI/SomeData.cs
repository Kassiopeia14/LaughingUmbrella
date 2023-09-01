using System.Text.Json.Serialization;

namespace MessageBusWebAPI
{
    public class SomeData
    {
        [JsonPropertyName("name")]
        public string Name { get; set; }

        [JsonPropertyName("age")]
        public int Age { get; set; }
    }
}
