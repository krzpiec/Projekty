using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Speedometer : MonoBehaviour
{
    public Rigidbody target;
    public CarController controller;
    public Slider nitroSlider;
    public float maxSpeed = 0.0f;
    public float nitroSliderMax = 0.63f;
    public float minSpeedArrowAngle;
    public float maxSpeedArrowAngle;
    public float deltaAngle;
    [Header("UI")]
    public Text speedLabel;
    public Text gearLabel;
    public RectTransform arrow;
    private float speed = 0.0f;
    private int gearNum;
    // Update is called once per frame

    private void handleNitrousBar()
    {
        nitroSlider.value = nitroSliderMax * controller.nitroLeft / controller.nitroMax;
    }

    private void Awake()
    {
        target = GameObject.FindGameObjectWithTag("Player").GetComponent<Rigidbody>();
        controller = GameObject.FindGameObjectWithTag("Player").GetComponent<CarController>();
    }
    void Update()
    {
        speed = target.velocity.magnitude * 3.6f;
        gearNum = controller.gearNum;
        speedLabel.text = speed.ToString("0");
       if(!controller.goingBackwards)
            gearLabel.text = gearNum.ToString("0");
        else
        {
            gearLabel.text = "R";
        }
        deltaAngle = minSpeedArrowAngle - maxSpeedArrowAngle;
        float temp = controller.engineRPM / 10000;
        float angle = minSpeedArrowAngle - temp * deltaAngle;
        if (angle < maxSpeedArrowAngle)
            angle = maxSpeedArrowAngle;
        arrow.transform.eulerAngles = new Vector3(0, 0, angle);

        handleNitrousBar();


    }
}
