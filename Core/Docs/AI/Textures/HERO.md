# Hero appearance textures — id reference

> AI-generated reference. Texture ids read from the `textures.big` TOC; the morph key table is
> decoded from `game.bin` `CHeroMorphDef` (10535 + 11246). Not original game documentation.

## How the morph system uses ids

`CEngineTextureMorphSet::AddTextureMorph(key, blend)` — the key is the `OriginalTextureIndex`
(a base sheet id), the blend's `TextureIndex` is the overlay drawn on top. Overlay and base share
the same sheet layout, so an overlay is only valid on the base it was authored for.

These are **texture ids**, not `game.bin` def indexes, and they never change between launches.

## Body-part base sheets

| Base | Id | Notes |
| --- | --- | --- |
| ARMS | 1248 | arms + hands |
| BACK | 1249 |  |
| FACE | 1250 |  |
| LEGS | 1251 |  |
| TORSO | 1252 | chest + stomach + shoulder |
| MOUTH | 1253 | only old/evil overlays — never tattooable |

These five (all but MOUTH) are the only sheets tattoos, body hair, scars, bruises and tans land on.

## All `OriginalTextureIndex` keys (49)

Every key the two `CHeroMorphDef` entries use (312 records = 156 × 2 identical, 154 unique).
`sN` = hero stat, arrows point at the overlay ids composited on that base.

| Key | Sheet | Morphs |
| --- | --- | --- |
| 1046 | HERO_EYE_NORMAL | s5→1050 · s6→1048 · s10→1049 |
| 1052 | HERO_HAIRBUZZ | s4→1055 · s7→1058 |
| 1053 | HERO_HAIRBUZZ_BALD_A | s4→1056 · s7→1059 |
| 1054 | HERO_HAIRBUZZ_BALD_B | s4→1057 · s7→1060 |
| 1061 | HERO_HAIRBASIN | s4→1064 · s7→1067 |
| 1062 | HERO_HAIRBASIN_BALD_A | s4→1065 · s7→1068 |
| 1063 | HERO_HAIRBASIN_BALD_B | s4→1066 · s7→1069 |
| 1070 | HERO_HAIRMOHAWK | s4→1071 · s7→1072 |
| 1073 | HERO_HAIRPLATS | s4→1076 · s7→1079 |
| 1074 | HERO_HAIRPLATS_BALD_A | s4→1077 · s7→1080 |
| 1075 | HERO_HAIRPLATS_BALD_B | s4→1078 · s7→1081 |
| 1082 | HERO_HAIRLONG | s4→1085 · s7→1088 |
| 1083 | HERO_HAIRLONG_BALD_A | s4→1086 · s7→1089 |
| 1084 | HERO_HAIRLONG_BALD_B | s4→1087 · s7→1090 |
| 1091 | HERO_HAIRYOUNG | s4→1094 · s7→1097 |
| 1092 | HERO_HAIRYOUNG_BALD_A | s4→1095 · s7→1098 |
| 1093 | HERO_HAIRYOUNG_BALD_B | s4→1096 · s7→1099 |
| 1100 | HERO_HAIRSHORT | s4→1103 · s7→1106 |
| 1101 | HERO_HAIRSHORT_BALD_A | s4→1104 · s7→1107 |
| 1102 | HERO_HAIRSHORT_BALD_B | s4→1105 · s7→1108 |
| 1109 | HERO_HAIRPONYTAIL | s4→1112 · s7→1115 |
| 1110 | HERO_HAIRPONYTAIL_BALD_A | s4→1113 · s7→1116 |
| 1111 | HERO_HAIRPONYTAIL_BALD_B | s4→1114 · s7→1117 |
| 1118 | HERO_BEARD_01 | s4→1133 · s7→1142 |
| 1119 | HERO_BEARD_02 | s4→1134 · s7→1143 |
| 1120 | HERO_BEARD_03 | s4→1135 · s7→1144 |
| 1121 | HERO_BEARDLONG_01 | s4→1129 · s7→1138 |
| 1122 | HERO_BEARDMUTTON_01 | s4→1130 · s7→1139 |
| 1123 | HERO_BEARDCHIN_01 | s4→1127 · s7→1136 |
| 1124 | HERO_BEARDSTRIP_01 | s4→1128 · s7→1137 |
| 1125 | HERO_BEARDTRAMP_01 | s4→1132 · s7→1141 |
| 1126 | HERO_BEARDWATSON_01 | s4→1131 · s7→1140 |
| 1145 | HERO_TASHCHINESE_01 | s4→1151 · s7→1157 |
| 1146 | HERO_TASHSMALL_01 | s4→1152 · s7→1158 |
| 1147 | HERO_TASHSMITH_01 | s4→1153 · s7→1159 |
| 1148 | HERO_TASHTRADER_01 | s4→1155 · s7→1161 |
| 1149 | HERO_TASHKHG_01 | s4→1154 · s7→1160 |
| 1150 | HERO_TASHSHERIFF_01 | s4→1156 · s7→1162 |
| 1233 | — *(missing in TLC)* | s5→1223 · s6→1016, 1230 · s10→1005 |
| 1234 | — *(missing in TLC)* | s5→1227 · s6→1015, 1232 · s8→980 · s9→981 · s10→1007 |
| 1235 | — *(missing in TLC)* | s5→1226 · s6→1017, 1229 · s8→979 · s10→1006 |
| 1236 | — *(missing in TLC)* | s5→1225 · s6→1018, 1231 · s8→978 · s10→1004 |
| 1237 | — *(missing in TLC)* | s5→1224 · s6→1014, 1228 · s8→977 · s10→1003 |
| 1248 | HERO_SKIN_ARMS | s5→990, 1021 · s6→1010, 1243 · s7→994, 1238 · s8→972 · s10→998 · s11→982, 983 |
| 1249 | HERO_SKIN_BACK | s5→991, 1022 · s6→1011, 1244 · s7→995, 1239 · s8→973 · s10→999 · s11→984, 985 |
| 1250 | HERO_SKIN_FACE | s3→1025 · s5→1019, 1026 · s6→1008, 1245 · s7→1027, 1240 · s10→1000 · s11→1025 |
| 1251 | HERO_SKIN_LEGS | s5→992, 1023 · s6→1012, 1246 · s7→996, 1241 · s8→974 · s10→1001 · s11→986, 987 |
| 1252 | HERO_SKIN_TORSO | s5→993, 1020 · s6→1009, 1247 · s7→997, 1242 · s8→975 · s9→976 · s10→1002 · s11→988, 989 |
| 1253 | HERO_SKIN_MOUTH | s5→1024 · s6→1013 |

Stat meanings: `s3` stubble, `s4` hair age, `s5` skin age, `s6` evil, `s7` good, `s8` muscle,
`s9` fatness, `s10` will, `s11` body hair. Layer, for reference: 0 tan/antitan, 2 muscle, 3 will,
4 evil/blonde, 5 old, 7 body hair/stubble, 8 secondary old hair.

⚠ `1233–1237` (`HERO_BUMP_SKIN_*`) are valid keys but **inert in TLC**: neither those
sheets nor their 25 overlays exist in the retail texture bank.

## Tattoo overlays

| Range | Count | Contents |
| --- | --- | --- |
| 906–962 | 57 | named designs (HC, KHG, KHGWAR, SS, plus NPC ones) |
| 1030–1043 | 14 | generic per-part sheets |

Usable ids per part:

| Part | Ids |
| --- | --- |
| ARMS | 909, 929, 934, 1030–1032 |
| BACK | 906–908, 910–915, 930, 935–937, 1033–1035 |
| FACE | 916–921, 931, 938–940, 945–955, 1036–1038 |
| TORSO | 922–928, 933, 942–944, 1041–1043 |
| LEGS | 932, 941, 1039, 1040 |

Tattoo records are **not** in `TextureMorphs` — they arrive at runtime through the tattoo cards
(`CTattooDef`), so any base/overlay pair can be produced by the card system.

## Body hair

Ids 982–997 (16 sheets: ARMS/BACK/LEGS/TORSO × {1A, 1B, OLD, BLONDE}).
They composite onto 1248/1249/1251/1252 exactly like tattoos — there is no FACE or MOUTH variant.

## Head hair, beards, moustaches

| Style | Base ids | Colour overlays (old / blonde) | Notes |
| --- | --- | --- | --- |
| WHOREWIG | 1051 | — / — | barber wig item — not a morph key |
| BUZZ | 1052–1054 | 1055–1057 / 1058–1060 | morph key + 2 bald variants |
| BASIN | 1061–1063 | 1064–1066 / 1067–1069 | morph key + 2 bald variants |
| MOHAWK | 1070 | 1071 / 1072 | morph key, no bald variants |
| PLATS | 1073–1075 | 1076–1078 / 1079–1081 | morph key + 2 bald variants |
| LONG | 1082–1084 | 1085–1087 / 1088–1090 | morph key + 2 bald variants |
| YOUNG | 1091–1093 | 1094–1096 / 1097–1099 | morph key + 2 bald variants |
| SHORT | 1100–1102 | 1103–1105 / 1106–1108 | morph key + 2 bald variants |
| PONYTAIL | 1109–1111 | 1112–1114 / 1115–1117 | morph key + 2 bald variants |

| Group | Base ids | Old | Blonde |
| --- | --- | --- | --- |
| Beards (9) | 1118–1126 | 1127–1135 | 1136–1144 |
| Moustaches (6) | 1145–1150 | 1151–1156 | 1157–1162 |

Hair/beard/moustache keys only morph for age (`s4` → OLD) and good (`s7` → BLONDE).

## Eyes

Eyes are their own material, not a skin part:

| Item | Id |
| --- | --- |
| `HERO_EYE_NORMAL` (base, also a morph key) | 1046 |
| `COMP_HERO_EYE_BERSERK` | 1044 |
| `HERO_EYESHADOW_32` | 1045 |
| `COMP_HERO_EYE_BLIND` | 1047 |
| `COMP_HERO_EYE_EVIL` | 1048 |
| `COMP_HERO_EYE_WILL` | 1049 |
| `COMP_HERO_EYE_OLD` | 1050 |
| shared iris / eye-colour set | 3950–3959 |

Mesh: `MESH_HERO_EYE` (graphics.big `MBANK_ALLMESHES` id 120), not the body `MESH_HERO` (4299).
Eyes have age/evil/will/blind/berserk morphs but no tattoo, scar, body-hair or tan slot.

## Skin state overlays, scars, bruises

| Group | Ids |
| --- | --- |
| berserk | 966–971 |
| muscle | 972–976 |
| will | 998–1002 |
| evil | 1008–1013 |
| old | 1019–1024 |
| stubble | 1025–1029 |
| tan | 1238–1242 |
| anti-tan | 1243–1247 |
| scars | 1165–1186 |
| bruises | 1209–1222 |

## Other hero sheets (not morph targets)

| Group | Ids |
| --- | --- |
| young / teen hero | 792–794, 1254 |
| starting armour (clothing) | 47–61 |
| ability icons | 523–528 |
| hair inventory cards | 1372–1396 |
| horns | 963–965 |

## Caveats

- Bump/normal ids `1233–1237` and their overlays do not exist in the TLC bank; those morph
  records are dead weight, and they are exactly the id gaps 977–981, 1003–1007, 1014–1018,
  1223–1237.
- `HERO_HAIRWHOREWIG` (1051) is a barber item texture, never a morph key.
- Teeth, tongue, nails have no hero sheets in this bank.
- Armour/clothing uses the separate `TEXTURE_HERO_*` prefix (103 sheets) and is unrelated.
