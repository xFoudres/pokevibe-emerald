#include "global.h"
#include "menu.h"
#include "text.h"
#include "window.h"
#include "strings.h"
#include "string_util.h"

static const struct WindowTemplate sWalletWindowTemplate =
{
    .bg = 0,
    .tilemapLeft = 2,
    .tilemapTop = 2,
    .width = 26,
    .height = 8,
    .paletteNum = 15,
    .baseBlock = 0x1A0
};

void Task_OpenWalletMenu(u8 taskId)
{
    u8 windowId = AddWindow(&sWalletWindowTemplate);
    u8 trainerIdStr[12]; // "0x" + 8 hex digits + null
    u32 trainerId = GetTrainerId(gSaveBlock2Ptr->playerTrainerId);

    DrawStdWindowFrame(windowId, FALSE);
    ConvertIntToHexStringN(trainerIdStr, trainerId, STR_CONV_MODE_LEADING_ZEROS, 8);
    trainerIdStr[0] = CHAR_0; // Prefix with "0x"
    trainerIdStr[1] = CHAR_x;
    AddTextPrinterParameterized(windowId, FONT_NORMAL, gText_WalletID, 0, 1, 0, NULL);
    AddTextPrinterParameterized(windowId, FONT_NORMAL, trainerIdStr, 0, 17, 0, NULL);
    gTasks[taskId].data[0] = windowId;
    gTasks[taskId].func = Task_WalletMenuWait;
}

static void Task_WalletMenuWait(u8 taskId)
{
    if (JOY_NEW(B_BUTTON))
    {
        u8 windowId = gTasks[taskId].data[0];
        ClearStdWindowAndFrameToTransparent(windowId, TRUE);
        RemoveWindow(windowId);
        DestroyTask(taskId);
    }
}
