#include <lvmx.h>

#define APP_NUM 16


int main() {


	int splash = createSlotFromTemplate("UIXempty");
	int splashText = createSlotFromTemplate("UIXtext");
	setDVString(splashText, "content", "Gammalab");
	setDVFloat(splashText, "R", 0.019607843137255f);
	setDVFloat(splashText, "G", 0.949019607843137f);
	setDVFloat(splashText, "B", 0.949019607843137f);
	setSlotParent(splashText, splash);
	setSlotParent(splash, UIXROOT_SLOT);

	int wrap = createSlotFromTemplate("UIXempty");

	int headerRect = createSlotFromTemplate("UIXempty");
	setDVFloat(headerRect, "Amy", 0.9f);
	setSlotParent(headerRect, wrap);

	int headerText = createSlotFromTemplate("UIXtext");
	setDVString(headerText, "content", "HOME");
	setDVFloat(headerText, "size", 48.0f);
	setDVFloat(headerText, "R", 0.019607843137255f);
	setDVFloat(headerText, "G", 0.949019607843137f);
	setDVFloat(headerText, "B", 0.949019607843137f);
	setSlotParent(headerText, headerRect);

	int bodyRect = createSlotFromTemplate("UIXempty");
	setDVFloat(bodyRect, "AMy", 0.9f);
	setSlotParent(bodyRect, wrap);

	int body = createSlotFromTemplate("UIXlayoutV");
	setDVInt(body, "alignV", 0);
	setDVFloat(body, "padTop", 4.0f);
	setDVFloat(body, "padBottom", 4.0f);
	setDVFloat(body, "padLeft", 4.0f);
	setDVFloat(body, "padRight", 4.0f);
	setDVFloat(body, "spacing", 4.0f);
	setSlotParent(body, bodyRect);

	int appButtonTemp = createSlotFromTemplate("UIXbutton");
	int appButtonImg  = createSlotFromTemplate("UIXimage");
	setDVFloat(appButtonImg, "R", 0.011764705882353f);
	setDVFloat(appButtonImg, "G", 0.396078431372549f);
	setDVFloat(appButtonImg, "B", 0.549019607843137f);
	setSlotParent(appButtonImg, appButtonTemp);
	int appButtonText = createSlotFromTemplate("UIXtext");
	setDVFloat(appButtonText, "R", 0.8f);
	setDVFloat(appButtonText, "G", 0.8f);
	setDVFloat(appButtonText, "B", 0.8f);
	setSlotParent(appButtonText, appButtonImg);

	int layoutElem = createSlotFromTemplate("UIXlayoutElem");
	setDVFloat(layoutElem, "minH", 32.0f);


	int i;
	int appitr = 0;
	int textbuff[32];
	int appNameBuff[64];
	int app_buttons[APP_NUM];
	int appIDs[APP_NUM];
	for (i = 0; i < APP_NUM; i++) {
		format(textbuff, "AppFlag%d", i);
		if (getDVInt(DEVICEROOT_SLOT, textbuff) != 0) {
			format(textbuff, "AppName%d", i);
			getDVString(DEVICEROOT_SLOT, textbuff, appNameBuff);
			setDVString(appButtonText, "content", appNameBuff);
			int newLayout = dupSlot(layoutElem);
			int newbutton = dupSlot(appButtonTemp);
			setSlotParent(newbutton, newLayout);
			setSlotParent(newLayout, body);
			appIDs[appitr] = i;
			app_buttons[appitr++] = newbutton;
		}
	}
	destroySlot(splash);
	setSlotParent(wrap, UIXROOT_SLOT);


	setDVInt(DEVICEROOT_SLOT, "OVERCLOCK", 10);

	while (1) {
		for (i = 0; i < appitr; i++) {
			if (getDVInt(app_buttons[i], "pressed") != 0) {
				setDVInt(DEVICEROOT_SLOT, "NEXTLOAD", appIDs[i]);
				setDVInt(DEVICEROOT_SLOT, "RESET", 1);
			}
		}
	}

}

