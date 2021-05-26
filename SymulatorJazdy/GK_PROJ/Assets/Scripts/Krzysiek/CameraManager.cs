using System.Collections;
using System.Collections.Generic;
using UnityEngine;



public class CameraManager : MonoBehaviour
{
    public GameObject focusOn;
   // public InputManager inp;
    public float height = 2f;
    public float distance = 2f;
    [Range(0,5)]public float nitroDampening;
    [Range(0, 20)] public float followDampening;
    public float defaultFOV;
    public float nitroFOV;
    public float addNitroFOV = 20f;

    void Start()
    {
        defaultFOV = Camera.main.fieldOfView;
        nitroFOV = defaultFOV + addNitroFOV;
        focusOn = GameObject.FindGameObjectWithTag("Player");
    }


   
    void FixedUpdate()
    {
        if(focusOn.GetComponent<InputManager>().nitro)
        {
            Camera.main.fieldOfView = Mathf.Lerp(Camera.main.fieldOfView, nitroFOV, nitroDampening * Time.deltaTime);
        }
        else
        {
            Camera.main.fieldOfView = Mathf.Lerp(Camera.main.fieldOfView, defaultFOV, nitroDampening * Time.deltaTime);
        }




        if (focusOn.GetComponent<InputManager>().cameraLeft)
        {
            transform.position = focusOn.transform.position + focusOn.transform.TransformDirection(new Vector3(-distance*1.5f, height, 0f));
        }
        else if (focusOn.GetComponent<InputManager>().cameraRight)
        {
            transform.position = focusOn.transform.position + focusOn.transform.TransformDirection(new Vector3(distance * 1.5f, height, 0f));
        }
        else
        {
            transform.position = Vector3.Lerp(transform.position, focusOn.transform.position + focusOn.transform.TransformDirection(new Vector3(0f, height, -distance)), followDampening * Time.deltaTime);
        }
       
        transform.LookAt(focusOn.transform);
        
    }
}
