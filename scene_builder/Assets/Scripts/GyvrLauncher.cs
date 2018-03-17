using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using System.IO;
using System.Diagnostics;
using UnityEngine.SceneManagement;
using System.Threading;
using System;

public class GyvrLauncher : MonoBehaviour
{
    private Process gyvrEngineProcess = new Process();
    private XMLExport m_xmlExporter;

    private void SendDataToGyvrEngine()
    {
        m_xmlExporter = GetComponent<XMLExport>();
        m_xmlExporter.SceneToXML();
    }

    private void Start()
    {
        SendDataToGyvrEngine();
        RunGyvrEngine();
        QuitLauncher();
    }

    private void Debug(string p_message)
    {
        if (p_message.StartsWith("[INFO]"))
            UnityEngine.Debug.Log(p_message.Replace("[INFO]", ""));
        else if (p_message.StartsWith("[WARNING]"))
            UnityEngine.Debug.LogWarning(p_message.Replace("[WARNING]", ""));
        else if (p_message.StartsWith("[ERROR]"))
            UnityEngine.Debug.LogError(p_message.Replace("[ERROR]", ""));
        else
            UnityEngine.Debug.Log(p_message);
    }

    private void RunGyvrEngine()
    {
        string[] buildInfo = File.ReadAllLines("..\\vs2017\\unity_build_info.ini");

        gyvrEngineProcess.EnableRaisingEvents = true;
        gyvrEngineProcess.StartInfo.RedirectStandardOutput = true;
        gyvrEngineProcess.StartInfo.RedirectStandardError = true;
        gyvrEngineProcess.StartInfo.UseShellExecute = false;
        gyvrEngineProcess.StartInfo.CreateNoWindow = true;
        gyvrEngineProcess.StartInfo.WorkingDirectory = "..\\vs2017";
        gyvrEngineProcess.StartInfo.FileName = buildInfo[0].Replace("last_build_path=", "");
        gyvrEngineProcess.StartInfo.Arguments = SceneManager.GetActiveScene().name;
        gyvrEngineProcess.OutputDataReceived += (sender, args) => { if (args.Data != null) Debug(args.Data); };
        gyvrEngineProcess.ErrorDataReceived += (sender, args) => { if (args.Data != null) Debug(args.Data); };
        
        bool result = gyvrEngineProcess.Start();

        if (result)
        {
            gyvrEngineProcess.BeginOutputReadLine();
            gyvrEngineProcess.BeginErrorReadLine();
        }
        else
        {
            UnityEngine.Debug.LogError("[ERROR] Can't start GyvrEngine");
        }
    }

    private void QuitLauncher()
    {
        #if UNITY_EDITOR
            UnityEditor.EditorApplication.isPlaying = false;
        #else
             Application.Quit();
        #endif
    }
}
