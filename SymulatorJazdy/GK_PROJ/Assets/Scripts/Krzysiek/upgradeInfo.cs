using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class upgradeInfo : MonoBehaviour
{
    public GameObject trigger;
    void Start()
    {
       this.gameObject.SetActive(true);
    }

  
    void Update()
    {
        //Debug.Log(trigger.name);
        var ray = Camera.main.ScreenPointToRay(Input.mousePosition);
        RaycastHit hit;
        if(Physics.Raycast(ray, out hit))
        {
            Debug.Log(hit.collider.transform.name);
            if(hit.collider.transform.name == trigger.name)
            {
                Debug.Log("udalo sie");
            }
        }

    }
}
