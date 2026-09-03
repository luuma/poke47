Route104_PrettyPetalFlowerShop_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route104_PrettyPetalFlowerShop_OnTransition
	.byte 0

Route104_PrettyPetalFlowerShop_OnTransition:
	setflag FLAG_LANDMARK_FLOWER_SHOP
	goto_if_unset FLAG_MET_PRETTY_PETAL_SHOP_OWNER, Route104_PrettyPetalFlowerShop_EventScript_MoveShopOwner
	goto_if_unset FLAG_BADGE03_GET, Route104_PrettyPetalFlowerShop_EventScript_MoveShopOwner
	setflag FLAG_TEMP_1
	end

Route104_PrettyPetalFlowerShop_EventScript_MoveShopOwner::
	setobjectxyperm LOCALID_FLOWER_SHOP_OWNER, 4, 6
	end

Route104_PrettyPetalFlowerShop_EventScript_ShopOwner::
	lock
	faceplayer
	goto_if_set FLAG_TEMP_1, Route104_PrettyPetalFlowerShop_EventScript_SellDecorations
	msgbox Route104_PrettyPetalFlowerShop_Text_ThisIsPrettyPetalFlowerShop, MSGBOX_DEFAULT
	goto_if_set FLAG_MET_PRETTY_PETAL_SHOP_OWNER, Route104_PrettyPetalFlowerShop_EventScript_AlreadyMet
	setflag FLAG_MET_PRETTY_PETAL_SHOP_OWNER
	msgbox Route104_PrettyPetalFlowerShop_Text_IntroLearnAboutBerries, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, Route104_PrettyPetalFlowerShop_EventScript_ExplainBerries
	call_if_eq VAR_RESULT, NO, Route104_PrettyPetalFlowerShop_EventScript_DontExplainBerries
	release
	end

Route104_PrettyPetalFlowerShop_EventScript_AlreadyMet::
	msgbox Route104_PrettyPetalFlowerShop_Text_LearnAboutBerries, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, Route104_PrettyPetalFlowerShop_EventScript_ExplainBerries
	call_if_eq VAR_RESULT, NO, Route104_PrettyPetalFlowerShop_EventScript_DontExplainBerries
	release
	end

Route104_PrettyPetalFlowerShop_EventScript_ExplainBerries::
	msgbox Route104_PrettyPetalFlowerShop_Text_BerriesExplanation, MSGBOX_DEFAULT
	return

Route104_PrettyPetalFlowerShop_EventScript_DontExplainBerries::
	msgbox Route104_PrettyPetalFlowerShop_Text_FlowersBringHappiness, MSGBOX_DEFAULT
	return

Route104_PrettyPetalFlowerShop_EventScript_SellDecorations::
	message gText_PlayerWhatCanIDoForYou
	waitmessage
	pokemartdecoration2 Route104_PrettyPetalFlowerShop_Pokemart_Plants
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
Route104_PrettyPetalFlowerShop_Pokemart_Plants:
	.2byte DECOR_RED_PLANT
	.2byte DECOR_TROPICAL_PLANT
	.2byte DECOR_PRETTY_FLOWERS
	.2byte DECOR_COLORFUL_PLANT
	.2byte DECOR_BIG_PLANT
	.2byte DECOR_GORGEOUS_PLANT
	pokemartlistend

Route104_PrettyPetalFlowerShop_EventScript_WailmerPailGirl::
	lock
	faceplayer
	goto_if_unset FLAG_RECEIVED_WAILMER_PAIL, Route104_PrettyPetalFlowerShop_EventScript_GiveWailmerPail
        goto_if_unset FLAG_SHAYMIN_CAUGHT, Route104_PrettyPetalFlowerShop_EventScript_SecretExplanation
	msgbox Route104_PrettyPetalFlowerShop_Text_WailmerPailExplanation, MSGBOX_DEFAULT
	release
	end

Route104_PrettyPetalFlowerShop_EventScript_GiveWailmerPail::
	msgbox Route104_PrettyPetalFlowerShop_Text_YouCanHaveThis, MSGBOX_DEFAULT
	giveitem ITEM_WAILMER_PAIL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_WAILMER_PAIL
Route104_PrettyPetalFlowerShop_EventScript_SecretExplanation::
	msgbox Route104_PrettyPetalFlowerShop_Text_SecretExplanation, MSGBOX_DEFAULT
	release
	end

Route104_PrettyPetalFlowerShop_Text_SecretExplanation:
	.string "While BERRY plants are growing,\n"
	.string "water them with the WAILMER PAIL.\p"
	.string "Also, I'll let you in on a secret.\p"
	.string "Somewhere near here, I hear there's\n"
	.string "a hidden grassy paradise of flowers.\p"
	.string "If you keep generosity in your heart\n"
	.string "you might glimpse it for a moment!$"


Route104_PrettyPetalFlowerShop_EventScript_RandomBerryGirl::
	lock
	faceplayer
	dotimebasedevents
	goto_if_set FLAG_DAILY_FLOWER_SHOP_RECEIVED_BERRY, Route104_PrettyPetalFlowerShop_EventScript_AlreadyReceivedBerry
        goto_if_set FLAG_GRACIDEA, Route104_PrettyPetalFlowerShop_EventScript_RandomBerryGirlret
        goto_if_set FLAG_SHAYMIN_CAUGHT, Route104_PrettyPetalFlowerShop_EventScript_berrycount
Route104_PrettyPetalFlowerShop_EventScript_RandomBerryGirlret::
	msgbox Route104_PrettyPetalFlowerShop_Text_ImGrowingFlowers, MSGBOX_DEFAULT
	giverandomberry BERRY_ID_CHERI, BERRY_ID_PERSIM
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	setflag FLAG_DAILY_FLOWER_SHOP_RECEIVED_BERRY
	msgbox Route104_PrettyPetalFlowerShop_Text_MachineMixesBerries, MSGBOX_DEFAULT
	release
	end

Route104_PrettyPetalFlowerShop_EventScript_AlreadyReceivedBerry::
	msgbox Route104_PrettyPetalFlowerShop_Text_MachineMixesBerries, MSGBOX_DEFAULT
	release
	end

Route104_PrettyPetalFlowerShop_EventScript_berrycount::
        callnative BufferCountBerries @ buffers strvar1 with rough number of berries to 200, buffers var result with "is it over 200"
        goto_if_eq VAR_RESULT, TRUE, Route104_PrettyPetalFlowerShop_GiveGracidea
	msgbox Route104_beforesayinggrowflowers, MSGBOX_DEFAULT
        goto Route104_PrettyPetalFlowerShop_EventScript_RandomBerryGirlret
        end

Route104_PrettyPetalFlowerShop_GiveGracidea::
	msgbox Route104_beforesayinggrowflowers, MSGBOX_DEFAULT
        giveitem ITEM_GRACIDEA
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
        setflag FLAG_GRACIDEA
        release
        end

Route104_beforesayinggrowflowers:
	.string "Wow! You met Shaymin?\n"
	.string "I'm doing a big project for Shaymin!\p"
	.string "I want to grow its precious flower\n"
	.string "but it's really hard.\l"
	.string "The soil here isn't rich enough.\p"
	.string "I need someone to plant maybe {STR_VAR_1}\n"
	.string "more berries for me!$"

Route104_PrettyPetalFlowerShop_text_GiveGracidea:
	.string "Yay! The Shaymin trainer!\p"
	.string "I did it! I grew loads!\p"
	.string "Here! Take one!$"











