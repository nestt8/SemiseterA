﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TileEngine
{
    class MapCell
    {
        public List<int> BaseTiles = new List<int>();
        public List<int> HeightTiles = new List<int>();
        public List<int> TopperTiles = new List<int>();
        
        public bool Explored { get; set; }
        public bool Walkable { get; set; }
        public int SlopeMap { get; set; }

        public int TileID
        {
            get { return BaseTiles.Count > 0 ? BaseTiles[0] : 0; }
            set
            {
                if (BaseTiles.Count > 0)
                    BaseTiles[0] = value;
                else
                    AddBaseTile(value);
            }
        }

        public void AddHeightTile(int tileID)
        {
            HeightTiles.Add(tileID);
        }

        public void AddTopperTile(int tileID)
        {
            TopperTiles.Add(tileID);
        }

        public void AddBaseTile(int tileID)
        {
            BaseTiles.Add(tileID);
        }

        public MapCell(int tileID)
        {
            Explored = false;
            TileID = tileID;
            Walkable = true;
            SlopeMap = -1;
        }
    }
}
