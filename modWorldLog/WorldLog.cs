using System.Text.Json.Serialization;

namespace modWorldLog
{
    public class WorldLog : IWorldLog
    {
        private WorldInitialState WorldInitialState;

        Dictionary<int, Epoch> Epochs;

        public WorldLog() 
        {
            Epochs = new Dictionary<int, Epoch>();
        }

        public WorldInitialState getWorldInitialState()
        {
            return WorldInitialState;
        }

        public void setWorldInitialState(WorldInitialState _WorldInitialState)
        {
            WorldInitialState = _WorldInitialState;
        }

        public Epoch getEpoch(int epochNumber)
        {
            return Epochs[epochNumber];
        }

        public void setEpoch(Epoch epoch)
        {
            Epochs.Add(epoch.Number, epoch);
        }
    }
}