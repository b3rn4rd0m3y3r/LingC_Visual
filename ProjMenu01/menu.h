#define IDR_MEUMENU 200

IDR_MEUMENU MENU DISCARDABLE 
BEGIN
	POPUP "menu1" , CHECKED
	BEGIN
	MENUITEM "item1", ID_DO_MENU1_ITEM1, CHECKED
	MENUITEM "item2", ID_DO_MENU1_ITEM2, HELP
	MENUITEM "itemX", ID_DO_MENU1_ITEMX, INACTIVE
	END
END

