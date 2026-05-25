
# Download at https://www.hackdex.app/hack/poke47

# About `poke47`

![Image of a sewaddle running back and forth in snow making footprints while the player watches](https://images.hackdex.app/poke47/1773931253238-3.png)![Gif that shows the game's start menu, with Kyurem](https://images.hackdex.app/poke47/1777208057027-9.gif)![Image of the player flying to a new route - a dramatic canyon](https://images.hackdex.app/poke47/1773931248565-0.png) 
=========================================================================================================================================================================================================
![Image showing the autobattle mechanic - the player's Sliggoo is fighting a starly in the overworld!](https://images.hackdex.app/poke47/1776628470989-8.png)![Gif that shows an expanded region map](https://images.hackdex.app/poke47/1777211690399-1.gif)![Image showing an Inkay battling a Furfrou with its ability Opposite Day, inverting the type chart](https://images.hackdex.app/poke47/1773931251614-2.png)

Pokemon ____(4) _______(7) is a patch for Pokémon Emerald. It replaces all pokemon from gen 1-3 with pokémon from generations 4 to 7, with properly playtested and overhauled movepools, new abilities, new TMs, and a handful of new routes, shown in the gif above. 
[This ROM is **extensively documented**, courtesy of JTebbe's Obstagoon, and some excellent work by Menace.](https://menace791.github.io/poke47-docs/)

This is a from-scratch disassembly port of my previous QOL/engine hack, Altered Emerald. Along the way I have made a few cuts, a few map additions, and some extra changes:

- The population of Hoenn is replaced with mons from generations 4 to 7 and all of those are rebalanced with new movesets and abilities. All the items, moves, and abilities from Gen 9 (and Champions) have been gifted to those 350 Pokémon. There's a handful of **custom moves, new abilities, and new hold items** to play with, too, and these are virtually exclusive to the player - enemy trainers won't confuse you with them. Check out the link above.

- **A blitz of QOL changes**.A better list of reusable TMs and movetutors. A more sensible system for HMs (starting before gym 4). Berry farming that's actually engaging. A better Pokédex. New maps, routes, and cycle challenges. Access the PC from the party menu, and relearn moves/TMs from the summary screen. Pokabbie/Bivurnum/HashtagMarky's overworld encounters, Chris Piche's updated game corner, Merrp's follower pokemon, and a gen 9 battle engine. A proper, polished, disassembly hack.


- Vanilla+ Difficulty, and a Level Cap for those who prefer a challenge. it is a hat. Nuzlocking this game isn't for the faint of heart!


- (19/4) I've successfully coded Scarlet/Violet-style **overworld autobattling** to the game, from scratch, based on the follower pokemon and overworld pokemon code. Press A to let the mon following you roam freely. Different mons will behave in different ways.


# About Pokémon Emerald Game Corner Expansion

Hello! This is a tweaked version of Chris Piche's Game Corner Expansion feature branch made by me, AGSMGMaster64.
Currently, this adds a new config file that uses some flags by default but can be configured to other flags if necessary.
Some new music and changes to the Mauville Corner have been made as well, so keep that in mind if you plan to merge this into your
existing project. Credits to AsparagusEduardo for the basis of this merge here, I just mainly tweaked things around to help
out any developers who may want to use this as well.

Below is the rest of the original description from Chris Piche himself:

More specifically, this adds 4 pinball mini-games, Flappy Bird, Block Stacker, Snake, Blackjack, Voltorb Flip, Plinko, Mauville Derby, and Gacha Machines into the Game Corner.

Big thank you to huderlem (Pokemon Pinball to Emerald), and Pokeabbie (Voltorb Flip from Emerald Rogue). All I really did for these was some graphics, music, and code to work with coins. They deserve the real credits here.
Also thank you to Viperio, who made an initial Snake for Pokemon Emerald that I based my code on.

...
# About `pokeemerald-expansion`

![Gif that shows debugging functionality that is unique to pokeemerald-expansion such as rerolling Trainer ID, Cheat Start, PC from Debug Menu, Debug PC Fill, Pokémon Sprite Visualizer, Debug Warp to Map, and Battle Debug Menu](https://github.com/user-attachments/assets/cf9dfbee-4c6b-4bca-8e0a-07f116ef891c) ![Gif that shows overworld functionality that is unique to pokeemerald-expansion such as indoor running, BW2 style map popups, overworld followers, DNA Splicers, Gen 1 style fishing, OW Item descriptions, Quick Run from Battle, Use Last Ball, Wild Double Battles, and Catch from EXP](https://github.com/user-attachments/assets/383af243-0904-4d41-bced-721492fbc48e) ![Gif that shows off a number of modern Pokémon battle mechanics happening in the pokeemerald-expansion engine: 2 vs 1 battles, modern Pokémon, items, moves, abilities, fully customizable opponents and partners, Trainer Slides, and generational gimmicks](https://github.com/user-attachments/assets/50c576bc-415e-4d66-a38f-ad712f3316be)

<!-- If you want to re-record or change these gifs, here are some notes that I used: https://files.catbox.moe/05001g.md -->

**`pokeemerald-expansion`** is a GBA ROM hack base that equips developers with a comprehensive toolkit for creating Pokémon ROM hacks. **`pokeemerald-expansion`** is built on top of [pret's `pokeemerald`](https://github.com/pret/pokeemerald) decompilation project. **It is not a playable Pokémon game on its own.**

# [Features](FEATURES.md)

**`pokeemerald-expansion`** offers hundreds of features from various [core series Pokémon games](https://bulbapedia.bulbagarden.net/wiki/Core_series), along with popular quality-of-life enhancements designed to streamline development and improve the player experience. A full list of those features can be found in [`FEATURES.md`](FEATURES.md).

# [Credits](CREDITS.md)

 [![](https://img.shields.io/github/all-contributors/rh-hideout/pokeemerald-expansion/upcoming)](CREDITS.md)

If you use **`pokeemerald-expansion`**, please credit **RHH (Rom Hacking Hideout)**. Optionally, include the version number for clarity.

```
Based off RHH's pokeemerald-expansion 1.15.2 https://github.com/rh-hideout/pokeemerald-expansion/
```

Please consider [crediting all contributors](CREDITS.md) involved in the project!

# Choosing `pokeemerald` or **`pokeemerald-expansion`**

- **`pokeemerald-expansion`** supports multiplayer functionality with other games built on **`pokeemerald-expansion`**. It is not compatible with official Pokémon games.
- If compatibility with official games is important, use [`pokeemerald`](https://github.com/pret/pokeemerald). Otherwise, we recommend using **`pokeemerald-expansion`**.
- **`pokeemerald-expansion`** incorporates regular updates from `pokeemerald`, including bug fixes and documentation improvements.

# [Getting Started](INSTALL.md)

❗❗ **Important**: Do not use GitHub's "Download Zip" option as it will not include commit history. This is necessary if you want to update or merge other feature branches.

If you're new to git and GitHub, [Team Aqua's Asset Repo](https://github.com/Pawkkie/Team-Aquas-Asset-Repo/) has a [guide to forking and cloning the repository](https://github.com/Pawkkie/Team-Aquas-Asset-Repo/wiki/The-Basics-of-GitHub). Then you can follow one of the following guides:

## 📥 [Installing **`pokeemerald-expansion`**](INSTALL.md)
## 🏗️ [Building **`pokeemerald-expansion`**](INSTALL.md#Building-pokeemerald-expansion)
## 🚚 [Migrating from **`pokeemerald`**](INSTALL.md#Migrating-from-pokeemerald)
## 🚀 [Updating **`pokeemerald-expansion`**](INSTALL.md#Updating-pokeemerald-expansion)

# [Documentation](https://rh-hideout.github.io/pokeemerald-expansion/)

For detailed documentation, visit the [pokeemerald-expansion documentation page](https://rh-hideout.github.io/pokeemerald-expansion/).

# [Contributions](CONTRIBUTING.md)
If you are looking to [report a bug](CONTRIBUTING.md#Bug-Report), [open a pull request](CONTRIBUTING.md#Pull-Requests), or [request a feature](CONTRIBUTING.md#Feature-Request), our [`CONTRIBUTING.md`](CONTRIBUTING.md) has guides for each.

# [Community](https://discord.gg/6CzjAG6GZk)

[![](https://dcbadge.limes.pink/api/server/6CzjAG6GZk)](https://discord.gg/6CzjAG6GZk)

Our community uses the [ROM Hacking Hideout (RHH) Discord server](https://discord.gg/6CzjAG6GZk) to communicate and organize. Most of our discussions take place there, and we welcome anybody to join us!
