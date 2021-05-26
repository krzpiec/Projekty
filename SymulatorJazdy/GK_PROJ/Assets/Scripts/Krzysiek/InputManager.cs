using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class InputManager : MonoBehaviour
{
    public float vertical;
    public float horizontal;
    public bool headLightsState = false;
    public bool handBrakeStart = false;
    public bool handBrakeEnd = false;
    public bool handBrake = false;
    public bool cameraLeft = false;
    public bool cameraRight = false;
    public bool nitro = false;
    public bool gearDown = false;
    public bool gearUp = false;

    // Update is called once per frame
    void Update()
    {
        vertical = Input.GetAxis("Vertical");
        horizontal = Input.GetAxis("Horizontal");
        headLightsState = Input.GetKeyDown(KeyCode.L);
        handBrake = Input.GetKey(KeyCode.Space);
        cameraLeft = Input.GetKey(KeyCode.Alpha7);
        cameraRight = Input.GetKey(KeyCode.Alpha9);
        gearDown = Input.GetKeyDown(KeyCode.Q);
        gearUp = Input.GetKeyDown(KeyCode.E);
        nitro = Input.GetKey(KeyCode.LeftShift);
    }


}
