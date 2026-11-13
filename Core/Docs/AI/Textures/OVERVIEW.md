# Textures.big — complete id reference

> AI-generated reference. Every id read from the `textures.big` TOC; nothing here is original
> game documentation. Companion docs are split by family, see the file map below.

## What this covers

`data/graphics/pc/textures.big` holds **3956 texture entries**, ids **1–4356**
(400 ids unused). Every entry is listed in one of the catalogs.

| File | Entries | Id range | Contents |
| --- | --- | --- | --- |
| `HERO.md` | 354 | 47–3959 | hero appearance in depth (318 `HERO_*` sheets + iris + icons) |
| `CHARACTERS.md` | 547 | 1–4002 | hero/armour, NPCs, villagers, creatures, rival heroes |
| `REGIONS.md` | 1713 | 247–4297 | every map region + landscape |
| `OBJECTS.md` | 1378 | 7–4356 | inventory icons, weapons, world props, gameplay, misc |

Split check: the hero doc holds all 318 `HERO_*` / `COMP_HERO_*` / `YOUNGHERO_*` entries, the three
catalogs hold the other 3,638 — no overlap, 3,956 total.

## Entry format

Verified anchors, for anyone walking the TOC:

- The **id is a u32 16 bytes before the CRC constant**, not the TOC index — ids are sparse.
- Every record in this bank carries the same CRC `0x7C8D23C4` (bank constant, 8 bytes before
  the length-prefixed name).
- After the name: `[u32 hash][u32 1][u32 depLen][depPath]`, then the texture info block and
  the payload. The dep path is the source TGA and is not needed to read the entry.
- Names are either friendly (`HERO_SKIN_FACE`, `TEXTURE_VILLAGER_MAN_C_HAIR_1`) or a dev path
  (`[\DEV\…\ART3\REGIONS\BOWERSTONE\….TGA]`). Catalogs show `*BASENAME` for dev-path entries;
  the section heading is the folder it came from.
- New entries authored by a mod start at **id 4357** (current max + 1).

## Unused ids

Ids are sparse: 400 of the 4356 id slots are unused.
Largest gaps:

`32–35`, `480–484`, `592–594`, `602–605`, `713–715`, `879–883`, `977–981`, `1003–1007`, `1014–1018`, `1187–1208`, `1223–1237`, `1349–1351`, `1355–1357`, `2482–2485`, `2558–2576`, `2688–2692`, `3039–3045`, `3135–3151`, `3427–3431`, `3439–3442`, `3451–3454`, `3457–3459`, `3759–3762`, `3827–3833`, `4298–4354`

Plus 160 single unused ids scattered through the ranges.

## Related docs

- `HERO.md` — hero appearance in depth: the 49 `OriginalTextureIndex`
  keys decoded from `game.bin`, tattoo/hair/eye ids, morph stats and layers, caveats.
- Graphics (`graphics.big`) model ids are a different bank and are not covered here.

