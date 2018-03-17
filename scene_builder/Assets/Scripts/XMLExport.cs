using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class XMLExport : MonoBehaviour {

    private string m_fileName;
    private List<string> m_xmlLines;

    void ParseComponent(Component p_comp, string tabs)
    {
        string tab = "    ";

        m_xmlLines.Add(tabs + "<component>");

        string componentName = p_comp.GetType().ToString().Replace("UnityEngine.", "");
        m_xmlLines.Add(tabs + tab + "<name>" + componentName + "</name>");

        if (p_comp is Transform)
        {
            Transform casted = (Transform)p_comp;
            m_xmlLines.Add(tabs + tab + "<position>");
            m_xmlLines.Add(tabs + tab + tab + "<x>" + casted.position.x + "</x>");
            m_xmlLines.Add(tabs + tab + tab + "<y>" + casted.position.y + "</y>");
            m_xmlLines.Add(tabs + tab + tab + "<z>" + casted.position.z + "</z>");
            m_xmlLines.Add(tabs + tab + "</position>");
            m_xmlLines.Add(tabs + tab + "<rotation>");
            m_xmlLines.Add(tabs + tab + tab + "<x>" + casted.rotation.eulerAngles.x + "</x>");
            m_xmlLines.Add(tabs + tab + tab + "<y>" + casted.rotation.eulerAngles.y + "</y>");
            m_xmlLines.Add(tabs + tab + tab + "<z>" + casted.rotation.eulerAngles.z + "</z>");
            m_xmlLines.Add(tabs + tab + "</rotation>");
            m_xmlLines.Add(tabs + tab + "<scale>");
            m_xmlLines.Add(tabs + tab + tab + "<x>" + casted.localScale.x + "</x>");
            m_xmlLines.Add(tabs + tab + tab + "<y>" + casted.localScale.y + "</y>");
            m_xmlLines.Add(tabs + tab + tab + "<z>" + casted.localScale.z + "</z>");
            m_xmlLines.Add(tabs + tab + "</scale>");
        }
        else if (p_comp is MeshRenderer)
        {
            m_xmlLines.Add(tabs + tab + "<meshName>" + p_comp.GetComponent<MeshRenderer>().meshToLoad + "</meshName>");
        }
        else if (p_comp is Camera)
        {

        }
        else if (p_comp is Light)
        {

        }

        m_xmlLines.Add(tabs + "</component>");
    }

    void ParseGameObject(GameObject p_gameObject, uint tabs)
    {
        string tabString = "";
        string tab = "    ";

        for (uint i = 0; i < tabs; ++i)
            tabString += tab;

        m_xmlLines.Add(tabString + "<gameobject>");
        m_xmlLines.Add(tabString + tab + "<name>" + p_gameObject.name + "</name>");

        if (p_gameObject.GetComponents<Component>()[0] != null)
        {
            m_xmlLines.Add(tabString + tab + "<components>");
            foreach (Component component in p_gameObject.GetComponents<Component>())
            {
                ParseComponent(component, tabString + tab + tab);
            }
            m_xmlLines.Add(tabString + tab + "</components>");
        }

        if (p_gameObject.transform.childCount > 0)
        {
            m_xmlLines.Add(tabString + tab + "<childs>");
            foreach (Transform child in p_gameObject.transform)
            {
                ParseGameObject(child.gameObject, tabs + 1);
            }
            m_xmlLines.Add(tabString + tab + "</childs>");
        }
        m_xmlLines.Add(tabString + "</gameobject>");
    }

    public void SceneToXML()
    {
        m_fileName = SceneManager.GetActiveScene().name;
        m_xmlLines = new List<string>();

        m_xmlLines.Add("<gameobjects>");

        foreach (Transform child in transform)
        {
            ParseGameObject(child.gameObject, 1);
        }

        m_xmlLines.Add("</gameobjects>");

        System.IO.File.WriteAllLines("../scene_graphs/unity_scenes/" + m_fileName + ".xml", m_xmlLines.ToArray());
    }
}
