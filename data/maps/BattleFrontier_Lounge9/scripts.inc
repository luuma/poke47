BattleFrontier_Lounge9_MapScripts::
	.byte 0

BattleFrontier_Lounge9_StoneSeller::
	lock
	faceplayer
	message BattleFrontier_Lounge9_Text_StoneSeller
	waitmessage
	pokemart BattleFrontier_Lounge9_Pokemart_Stones
	msgbox BattleFrontier_Lounge9_Text_StoneSellerAgain, MSGBOX_DEFAULT
	release
	end


BattleFrontier_Lounge9_Text_StoneSeller:
	.string "You need gems. I see it.\p"
	.string "I see a gleam in your eyes\n"
	.string "of someone who is desperate to\l"
	.string "complete their NATIONAL POKéDEX.\p"
	.string "I'm your girl.$"

BattleFrontier_Lounge9_Text_StoneSellerAgain:
	.string "Come again!$"


	.align 2
BattleFrontier_Lounge9_Pokemart_Stones:
	.2byte ITEM_WATER_STONE
	.2byte ITEM_FIRE_STONE
	.2byte ITEM_THUNDER_STONE
	.2byte ITEM_LEAF_STONE
	.2byte ITEM_ICE_STONE
	pokemartlistend

