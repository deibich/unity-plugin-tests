using System;
using System.Runtime.InteropServices;

public class NativeActionTest : Action
{
    public class NativeActionTestRenderEventIDS : ActionRenderEventIDS
    {
        const int ACTION_TEST_UPDATE = NATIVE_ACTION_RENDER_EVENT_ID_COUNT;

        const int NATIVE_ACTION_TEST_RENDER_EVENT_ID_COUNT = ACTION_TEST_UPDATE + 1;
    }

    const string dllName = "NativeActionTest";

    [DllImport(dllName, EntryPoint = "createAction")]
    private static extern IntPtr createActionExtern();


    [DllImport(dllName, EntryPoint = "destroyAction")]
    private static extern void destroyActionExtern(IntPtr nativeAction);

    [DllImport(dllName, EntryPoint = "getRenderEventIDOffset")]
    private static extern int getRenderEventIDOffsetExtern(IntPtr nativeAction);

    protected override IntPtr create()
    {
        return createActionExtern();
    }

    protected override void destroy(IntPtr actionPointer)
    {
        destroyActionExtern(actionPointer);
    }

    protected override int getRenderEventIdOffset()
    {
        return getRenderEventIDOffsetExtern(ActionPointer);
    }

    protected override void Start()
    {
        base.Start();
        SetupAction();
    }

    private void OnDestroy()
    {
        TeardownAction();
    }
}
