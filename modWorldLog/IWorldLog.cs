using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace modWorldLog
{
    public interface IWorldLog
    {
        public WorldInitialState getWorldInitialState();

        public void setWorldInitialState(WorldInitialState _WorldInitialState);

        public Epoch getEpoch(int epochNumber);

        public void setEpoch(Epoch _Epoch);
    }
}
