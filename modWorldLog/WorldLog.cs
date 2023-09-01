using System.Text.Json.Serialization;

namespace modWorldLog
{
    public class WorldLog : IWorldLog
    {
        private WorldInitialState WorldInitialState;

        private List<Epoch> Epochs;

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

        public void setEpoch(Epoch _Epoch)
        {
            Epochs.Add(_Epoch);
        }
    }
}