using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

public class UnityNativePluginSequence : MonoBehaviour
{
    const string pluginName = "UnityNativePluginSequence";

    [DllImport(pluginName)]
    private static extern void logFromPlugin();

    private void Start()
    {
        logFromPlugin();
    }
}
