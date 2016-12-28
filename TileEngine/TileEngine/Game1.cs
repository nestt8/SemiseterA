using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;

namespace TileEngine
{
    /// <summary>
    /// This is the main type for your game
    /// </summary>
    public class Game1 : Microsoft.Xna.Framework.Game
    {
        enum GameState
        {
            MainMenu,
            Playing,
        }

        GameState currentGameState = GameState.MainMenu;

        Texture2D mainMenuBackground;
        MainMenuButton buttonPlay;

        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;

        TileMap myMap;
        Texture2D hilight;
        int squaresAcross = 17;        
        int squaresDown = 37;
        int baseOffsetX = -32;
        int baseOffsetY = -64;
        float heightRowDepthMod = 0.0000001f;

        SpriteFont pericles6;

        SpriteAnimation Vlad;

        public Game1()
        {
            graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
        }

        /// <summary>
        /// Allows the game to perform any initialization it needs to before starting to run.
        /// This is where it can query for any required services and load any non-graphic
        /// related content.  Calling base.Initialize will enumerate through any components
        /// and initialize them as well.
        /// </summary>
        protected override void Initialize()
        {
            // TODO: Add your initialization logic here
            this.IsMouseVisible = true;

            base.Initialize();
        }

        /// <summary>
        /// LoadContent will be called once per game and is the place to load
        /// all of your content.
        /// </summary>
        protected override void LoadContent()
        {
            // Create a new SpriteBatch, which can be used to draw textures.
            spriteBatch = new SpriteBatch(GraphicsDevice);

            mainMenuBackground = Content.Load<Texture2D>(@"Textures\background");
            buttonPlay = new MainMenuButton(Content.Load<Texture2D>(@"Textures\button_play"), graphics.GraphicsDevice);
            buttonPlay.SetPosition(new Vector2(350, 300));

            pericles6 = Content.Load<SpriteFont>(@"Fonts\Pericles6");
            Tile.TileSetTexture = Content.Load<Texture2D>(@"Textures\TileSets\part4_tileset");

            myMap = new TileMap(Content.Load<Texture2D>(@"Textures\TileSets\mousemap"),
                                Content.Load<Texture2D>(@"Textures\TileSets\part9_slopemaps"));
            hilight = Content.Load<Texture2D>(@"Textures\TileSets\hilight");

            Camera.ViewWidth = this.graphics.PreferredBackBufferWidth;
            Camera.ViewHeight = this.graphics.PreferredBackBufferHeight;
            Camera.WorldWidth = ((myMap.MapWidth - 2) * Tile.TileStepX);
            Camera.WorldHeight = ((myMap.MapHeight - 2) * Tile.TileStepY);
            Camera.DisplayOffset = new Vector2(baseOffsetX, baseOffsetY);

            Vlad = new SpriteAnimation(Content.Load<Texture2D>(@"Textures\Characters\T_Vlad_Sword_Walking_48x48"));

            Vlad.AddAnimation("WalkEast", 0, 48 * 0, 48, 48, 8, 0.1f);
            Vlad.AddAnimation("WalkNorth", 0, 48 * 1, 48, 48, 8, 0.1f);
            Vlad.AddAnimation("WalkNorthEast", 0, 48 * 2, 48, 48, 8, 0.1f);
            Vlad.AddAnimation("WalkNorthWest", 0, 48 * 3, 48, 48, 8, 0.1f);
            Vlad.AddAnimation("WalkSouth", 0, 48 * 4, 48, 48, 8, 0.1f);
            Vlad.AddAnimation("WalkSouthEast", 0, 48 * 5, 48, 48, 8, 0.1f);
            Vlad.AddAnimation("WalkSouthWest", 0, 48 * 6, 48, 48, 8, 0.1f);
            Vlad.AddAnimation("WalkWest", 0, 48 * 7, 48, 48, 8, 0.1f);

            Vlad.AddAnimation("IdleEast", 0, 48 * 0, 48, 48, 1, 0.2f);
            Vlad.AddAnimation("IdleNorth", 0, 48 * 0, 48, 48, 1, 0.2f);
            Vlad.AddAnimation("IdleNorthEast", 0, 48 * 0, 48, 48, 1, 0.2f);
            Vlad.AddAnimation("IdleNorthWest", 0, 48 * 0, 48, 48, 1, 0.2f);
            Vlad.AddAnimation("IdleSouth", 0, 48 * 0, 48, 48, 1, 0.2f);
            Vlad.AddAnimation("IdleSouthEast", 0, 48 * 0, 48, 48, 1, 0.2f);
            Vlad.AddAnimation("IdleSouthWest", 0, 48 * 0, 48, 48, 1, 0.2f);
            Vlad.AddAnimation("IdleWest", 0, 48 * 0, 48, 48, 1, 0.2f);

            Vlad.Position = new Vector2(100, 100);
            Vlad.drawOffset = new Vector2(-24, -38);
            Vlad.CurrentAnimation = "WalkEast";
            Vlad.IsAnimating = true;    

            // TODO: use this.Content to load your game content here
        }

        /// <summary>
        /// UnloadContent will be called once per game and is the place to unload
        /// all content.
        /// </summary>
        protected override void UnloadContent()
        {
            // TODO: Unload any non ContentManager content here
        }

        /// <summary>
        /// Allows the game to run logic such as updating the world,
        /// checking for collisions, gathering input, and playing audio.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Update(GameTime gameTime)
        {
            // Allows the game to exit
            if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed)
                this.Exit();

            MouseState mouse = Mouse.GetState();

            Vector2 moveVector = Vector2.Zero;
            Vector2 moveDir = Vector2.Zero;
            string animation = "";
            switch(currentGameState)
            {
                case GameState.Playing:
                    KeyboardState ks = Keyboard.GetState();

                    if (ks.IsKeyDown(Keys.NumPad7))
                    {
                        moveDir = new Vector2(-2, -1);
                        animation = "WalkNorthWest";
                        moveVector += new Vector2(-2, -1);
                    }

                    if (ks.IsKeyDown(Keys.NumPad8))
                    {
                        moveDir = new Vector2(0, -1);
                        animation = "WalkNorth";
                        moveVector += new Vector2(0, -1);
                    }

                    if (ks.IsKeyDown(Keys.NumPad9))
                    {
                        moveDir = new Vector2(2, -1);
                        animation = "WalkNorthEast";
                        moveVector += new Vector2(2, -1);
                    }

                    if (ks.IsKeyDown(Keys.NumPad4))
                    {
                        moveDir = new Vector2(-2, 0);
                        animation = "WalkWest";
                        moveVector += new Vector2(-2, 0);
                    }

                    if (ks.IsKeyDown(Keys.NumPad6))
                    {
                        moveDir = new Vector2(2, 0);
                        animation = "WalkEast";
                        moveVector += new Vector2(2, 0);
                    }

                    if (ks.IsKeyDown(Keys.NumPad1))
                    {
                        moveDir = new Vector2(-2, 1);
                        animation = "WalkSouthWest";
                        moveVector += new Vector2(-2, 1);
                    }

                    if (ks.IsKeyDown(Keys.NumPad2))
                    {
                        moveDir = new Vector2(0, 1);
                        animation = "WalkSouth";
                        moveVector += new Vector2(0, 1);
                    }

                    if (ks.IsKeyDown(Keys.NumPad3))
                    {
                        moveDir = new Vector2(2, 1);
                        animation = "WalkSouthEast";
                        moveVector += new Vector2(2, 1);
                    }

                    if (myMap.GetCellAtWorldPoint(Vlad.Position + moveDir).Walkable == false)
                        moveDir = Vector2.Zero;

                    if (Math.Abs(myMap.GetOverallHeight(Vlad.Position) - myMap.GetOverallHeight(Vlad.Position + moveDir)) > 10)
                        moveDir = Vector2.Zero;

                    if (moveDir.Length() != 0)
                    {
                        Vlad.MoveBy((int)moveDir.X, (int)moveDir.Y);
                        if (Vlad.CurrentAnimation != animation)
                            Vlad.CurrentAnimation = animation;
                    }
                    else
                    {
                        Vlad.CurrentAnimation = "Idle" + Vlad.CurrentAnimation.Substring(4);
                    }

                    float vladX = MathHelper.Clamp(Vlad.Position.X, 0 + Vlad.drawOffset.X, Camera.WorldWidth);
                    float vladY = MathHelper.Clamp(Vlad.Position.Y, 0 + Vlad.drawOffset.Y, Camera.WorldHeight);
                    Vlad.Position = new Vector2(vladX, vladY);
                    Vector2 testPosition = Camera.WorldToScreen(Vlad.Position);

                    if (testPosition.X < 100)
                    {
                        Camera.Move(new Vector2(testPosition.X - 100, 0));
                    }

                    if (testPosition.X > (Camera.ViewWidth - 100))
                    {
                        Camera.Move(new Vector2(testPosition.X - (Camera.ViewWidth - 100), 0));
                    }

                    if (testPosition.Y < 100)
                    {
                        Camera.Move(new Vector2(0, testPosition.Y - 100));
                    }

                    if (testPosition.Y > (Camera.ViewHeight - 100))
                    {
                        Camera.Move(new Vector2(0, testPosition.Y - (Camera.ViewHeight - 100)));
                    }
                    // TODO: Add your update logic here
                    Vlad.Update(gameTime);
                    break;

                    

                case GameState.MainMenu:
                    if (buttonPlay.isClicked)
                        currentGameState = GameState.Playing;
                    buttonPlay.Update(mouse);
                    break;

            }

            

            base.Update(gameTime);
        }

        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.Black);

            spriteBatch.Begin(SpriteSortMode.BackToFront, BlendState.AlphaBlend);

            switch(currentGameState)
            {
                case GameState.Playing:
                    Vector2 firstSquare = new Vector2(Camera.Location.X / Tile.TileStepX, Camera.Location.Y / Tile.TileStepY);
                    int firstX = (int)firstSquare.X;
                    int firstY = (int)firstSquare.Y;

                    Vector2 squareOffset = new Vector2(Camera.Location.X % Tile.TileStepX, Camera.Location.Y % Tile.TileStepY);
                    int offsetX = (int)squareOffset.X;
                    int offsetY = (int)squareOffset.Y;

                    float maxdepth = ((myMap.MapWidth + 1) + ((myMap.MapHeight + 1) * Tile.TileWidth)) * 10;
                    float depthOffset;
                    Point vladMapPoint = myMap.WorldToMapCell(new Point((int)Vlad.Position.X, (int)Vlad.Position.Y));

                    for (int y = 0; y < squaresDown; y++)
                    {
                        int rowOffset = 0;
                        if ((firstY + y) % 2 == 1)
                            rowOffset = Tile.OddRowOffset;
                        for (int x = 0; x < squaresAcross; x++)
                        {
                            int mapx = (firstX + x);
                            int mapy = (firstY + y);
                            depthOffset = 0.7f - ((mapx + (mapy * Tile.TileWidth)) / maxdepth);
                            if ((mapx >= myMap.MapWidth) || (mapy >= myMap.MapHeight))
                                continue;
                            foreach (int tileID in myMap.Rows[mapy].Columns[mapx].BaseTiles)
                            {
                                spriteBatch.Draw(
                                    Tile.TileSetTexture,
                                    Camera.WorldToScreen(
                                        new Vector2((mapx * Tile.TileStepX) + rowOffset, mapy * Tile.TileStepY)),
                                    Tile.GetSourceRectangle(tileID),
                                    Color.White,
                                    0.0f,
                                    Vector2.Zero,
                                    1.0f,
                                    SpriteEffects.None,
                                    1.0f);
                            }
                            int heightRow = 0;

                            foreach (int tileID in myMap.Rows[mapy].Columns[mapx].HeightTiles)
                            {
                                spriteBatch.Draw(
                                    Tile.TileSetTexture,
                                    Camera.WorldToScreen(
                                        new Vector2(
                                           (mapx * Tile.TileStepX) + rowOffset,
                                            mapy * Tile.TileStepY - (heightRow * Tile.HeightTileOffset))),
                                    Tile.GetSourceRectangle(tileID),
                                    Color.White,
                                    0.0f,
                                    Vector2.Zero,
                                    1.0f,
                                    SpriteEffects.None,
                                    depthOffset - ((float)heightRow * heightRowDepthMod));
                                heightRow++;
                            }

                            foreach (int tileID in myMap.Rows[y + firstY].Columns[x + firstX].TopperTiles)
                            {
                                spriteBatch.Draw(
                                    Tile.TileSetTexture,
                                    Camera.WorldToScreen(
                                        new Vector2((mapx * Tile.TileStepX) + rowOffset, mapy * Tile.TileStepY)),
                                    Tile.GetSourceRectangle(tileID),
                                    Color.White,
                                    0.0f,
                                    Vector2.Zero,
                                    1.0f,
                                    SpriteEffects.None,
                                    depthOffset - ((float)heightRow * heightRowDepthMod));
                            }

                            if ((mapx == vladMapPoint.X) && (mapy == vladMapPoint.Y))
                                Vlad.drawDepth = depthOffset - (float)(heightRow + 2) * heightRowDepthMod;
                            /*spriteBatch.DrawString(pericles6, (x + firstX).ToString() + ", " + (y + firstY).ToString(),
                            new Vector2((x * Tile.TileStepX) - offsetX + rowOffset + baseOffsetX + 24,
                            (y * Tile.TileStepY) - offsetY + baseOffsetY + 48), Color.White, 0f, Vector2.Zero,
                            1.0f, SpriteEffects.None, 0.0f);*/
                        }
                    }

                    Vlad.Draw(spriteBatch, 0, -myMap.GetOverallHeight(Vlad.Position));

                    Vector2 hilightLoc = Camera.ScreenToWorld(new Vector2(Mouse.GetState().X, Mouse.GetState().Y));
                    Point hilightPoint = myMap.WorldToMapCell(new Point((int)hilightLoc.X, (int)hilightLoc.Y));

                    int hilightrowOffset = 0;
                    if ((hilightPoint.Y) % 2 == 1)
                        hilightrowOffset = Tile.OddRowOffset;
                    spriteBatch.Draw(
                               hilight,
                               Camera.WorldToScreen(
                                   new Vector2(
                                       (hilightPoint.X * Tile.TileStepX) + hilightrowOffset,
                                       (hilightPoint.Y + 2) * Tile.TileStepY)),
                               new Rectangle(0, 0, 64, 32),
                               Color.White * 0.3f,
                               0.0f,
                               Vector2.Zero,
                               1.0f,
                               SpriteEffects.None,
                               0.0f);

                    break;
                case GameState.MainMenu:
                    spriteBatch.Draw(mainMenuBackground, new Rectangle(0, 0, this.graphics.PreferredBackBufferWidth,
                        this.graphics.PreferredBackBufferHeight), Color.White);
                    buttonPlay.Draw(spriteBatch);
                    break;

            }

            spriteBatch.End();
            // TODO: Add your drawing code here

            base.Draw(gameTime);
        }
    }
}
