using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;
using UnityEngine.Rendering;

public class UnityNativePluginD3D11Resources : MonoBehaviour
{
    const string pluginName = "UnityNativePluginD3D11Resources";

    [DllImport(pluginName)]
    static private extern IntPtr GetRenderEventAndDataFunc();

    [DllImport(pluginName)]
    static private extern IntPtr GetRenderEventFunc();

    RenderTexture rt;
    CommandBuffer cb1;
    RenderBuffer colorBuffer;

    CommandBuffer cb2;
    CommandBuffer cb3;

    // Start is called before the first frame update
    void Start()
    {
        CommandBuffer syncCommandBuffer = new CommandBuffer();
        syncCommandBuffer.IssuePluginEvent(GetRenderEventFunc(), 15);
        Graphics.ExecuteCommandBuffer(syncCommandBuffer);
        rt = new RenderTexture(128, 128, 1);
        rt.Create();

        colorBuffer = rt.colorBuffer;



        // cb1 = new CommandBuffer();
        // cb1.IssuePluginEventAndData(GetRenderEventAndDataFunc(), 17, colorBuffer.GetNativeRenderBufferPtr());
        // Camera.main.AddCommandBuffer(CameraEvent.AfterDepthTexture, cb1);

        cb2 = new CommandBuffer();
        cb2.IssuePluginEvent(GetRenderEventFunc(), 18);
        cb3 = new CommandBuffer();
        cb3.IssuePluginEvent(GetRenderEventFunc(), 19);

        Camera.main.AddCommandBuffer(CameraEvent.AfterDepthTexture, cb2);
        Camera.main.AddCommandBuffer(CameraEvent.BeforeForwardOpaque, cb3);
    }

    private void OnDestroy()
    {
        CommandBuffer syncCommandBuffer = new CommandBuffer();
        syncCommandBuffer.IssuePluginEvent(GetRenderEventFunc(), 16);
        Graphics.ExecuteCommandBuffer(syncCommandBuffer);
    }
}
