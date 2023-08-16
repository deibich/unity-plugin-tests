
using System;
using UnityEngine;

public abstract class Action : MonoBehaviour
{
    public class ActionRenderEventIDS
    {
        public const int ACTION_INITIALIZE = 0;

        public const int ACTION_TEARDOWN = 1;

        public const int NATIVE_ACTION_RENDER_EVENT_ID_COUNT = 2;
    }

    private ActionRuntime actionRuntime;

    private IntPtr actionPointer = IntPtr.Zero;

    private int _renderEventIdOffset = 0;

    public IntPtr ActionPointer => actionPointer;

    public int RenderEventIdOffset => _renderEventIdOffset;

    public int getRenderEventID(int baseRenderEventId)
    {
        return _renderEventIdOffset + baseRenderEventId;
    }

    protected abstract IntPtr create();

    protected abstract void destroy(IntPtr actionPointer);

    protected virtual void initialize()
    {
        actionRuntime.ExecuteImmediate(getRenderEventID(0), ActionPointer);
    }

    protected virtual void teardown()
    {
        actionRuntime.ExecuteImmediate(getRenderEventID(1), ActionPointer);
    }

    protected abstract int getRenderEventIdOffset();

    protected virtual void register()
    {
        actionRuntime.registerAction(this);
        _renderEventIdOffset = getRenderEventIdOffset();
    }

    protected virtual void unregister()
    {
        actionRuntime.unregisterAction(this);
    }

    protected void SetupAction()
    {
        if (actionPointer == IntPtr.Zero)
        {
            actionPointer = create();
            register();
            initialize();
        }
        else
        {
            Debug.LogError((object)"Action already setup");
        }
    }

    protected void TeardownAction()
    {
        if (actionPointer != IntPtr.Zero)
        {
            teardown();
            unregister();
            actionPointer = IntPtr.Zero;
        }
        else
        {
            Debug.LogError((object)"TeardownAction not possible");
        }
    }

    protected virtual void Start()
    {
        actionRuntime = ActionRuntime.Instance;
    }
}
