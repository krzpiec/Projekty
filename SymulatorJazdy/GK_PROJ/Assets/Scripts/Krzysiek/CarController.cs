using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
[RequireComponent(typeof(InputManager))]
[RequireComponent(typeof(Rigidbody))]
[RequireComponent(typeof(LightingManager))]
public class CarController : MonoBehaviour
{
    
    public enum driveType
    {
        frontWheels,
        rearWheels,
        allWheels
    }
    public enum transmissionType
    {
        automatic,
        manual
    }

    internal enum wheelPos
    {
        FR = 0,
        FL = 1,
        BR = 2,
        BL = 3
    }

    public string drivingSceneName = "Krzyszsiek_Scene";
    public InputManager inp;
    public LightingManager lightingManager;
    private WheelCollider[] throttleWheels = new WheelCollider[4];
    public List<ParticleSystem> nitroParticles;
    public List<GameObject> steerWheels;
    public List<GameObject> wheelMeshes;
    public Transform centerMass;
    public Rigidbody RigBod;
    [Header("Variables")]
    public AnimationCurve enginePower;
    [SerializeField] private transmissionType transmission;
    public float motorTorqueMultiplier;
    public float brakeMultiplayer;
    public float maxTurn = 20f;
    private float smoothTime = 0.09f;
    public float n2oThrust;
    public float brakeStrength;
    public float maxEngingeRPM = 7900f;
    public float minEngingeRPM = 5000;
    public float[] gears;
    public int totalGears = 4;
    public bool goingBackwards = false;
   [SerializeField] private driveType drive;
    public float nitroMax = 100f;
    public float nitroConsumption = 20f;
    public float nitroGain = 0.2f;
    public float nitroLeft = 100f;
    public float downForce = 100;
    public float radius = 6;
    [Header("Debug")]
    public float engineRPM;
    public float horsePower;
    public int gearNum = 1;
    public float wheelsRPM;
    public float setForwardFriction;
    public float setSidewaysFriction;
    public float [] forwardSlip = new float[4];
    public float[] sidewaysSlip = new float[4];
    public float[] motorTorque = new float[4];

    public static CarController Instance;
    
    
    void Awake ()
    {
        if (SceneManager.GetActiveScene().name != drivingSceneName)
            return;
        inp = GetComponent<InputManager>();
        RigBod = GetComponent<Rigidbody>();

        if(centerMass)
        {
            RigBod.centerOfMass = centerMass.transform.localPosition;
        }

       

        if(Instance != null)
        {
            Destroy(this.gameObject);
            return;
        }
        Instance = this;
        GameObject.DontDestroyOnLoad(this.gameObject);

        throttleWheels[0] = GameObject.FindGameObjectWithTag("FrontRightWheel").GetComponent<WheelCollider>();
        throttleWheels[1] = GameObject.FindGameObjectWithTag("FrontLeftWheel").GetComponent<WheelCollider>();
        throttleWheels[2] = GameObject.FindGameObjectWithTag("BackRightWheel").GetComponent<WheelCollider>();
        throttleWheels[3] = GameObject.FindGameObjectWithTag("BackLeftWheel").GetComponent<WheelCollider>();
        steerWheels[0] = GameObject.FindGameObjectWithTag("FrontLeftWheel");
        steerWheels[1] = GameObject.FindGameObjectWithTag("FrontRightWheel");
        wheelMeshes[1].transform.Rotate(0f, 180f, 0f);

        foreach (WheelCollider wheel in throttleWheels)
        {
            wheel.ConfigureVehicleSubsteps(5, 12, 15);
        }

    }

    void Update()
    {
        if(inp.headLightsState)
        {
            lightingManager.ToggleHeadlights();
        }
        
         lightingManager.HandleBreaklights(inp.handBrake);
        


        if(transmission == transmissionType.manual)
        {
            shiftGearsManual();
        }
            

    }

    void FixedUpdate()
    {
        if (SceneManager.GetActiveScene().name != drivingSceneName)
        {
            return;
        }
        calculateEnginePower();

        wheelsHorizontal();

        wheelsVertical();

        animateWheels();

        applyDownForce();

        calculateWheelsRPM();
        getFriction();

        nitrous();

        if (transmission == transmissionType.automatic)
        {
            shiftGearsAutomatic();
        }


    }

    public void startVehicle()
    {

        foreach (WheelCollider wheel in throttleWheels)
        {
            wheel.brakeTorque =0f;
        }
    }
    public void stopVehicle()
    {

        foreach(WheelCollider wheel in throttleWheels)
        {
            wheel.motorTorque = 0f;
            wheel.brakeTorque = Mathf.Infinity;
        }
        steerWheels[0].transform.localEulerAngles = Vector3.zero;
        steerWheels[1].transform.localEulerAngles = Vector3.zero;
        RigBod.velocity = Vector3.zero;
        RigBod.angularVelocity = Vector3.zero;
    }

    void wheelsHorizontal()
    {

        //SET MOTOR TORQUE
       if(drive == driveType.allWheels)
        {
            for (int i = 0; i < 4; i++)
            {
                //  throttleWheels[i].motorTorque = motorTorqueMultiplayer * strengthCoefficient * Time.deltaTime * inp.vertical;
                throttleWheels[i].motorTorque = horsePower * motorTorqueMultiplier * Time.deltaTime / 4;
                throttleWheels[i].brakeTorque = 0f;
            }
        }
       else if(drive == driveType.rearWheels)
        {
            for (int i=2; i<4; i++)
            {
                //  throttleWheels[i].motorTorque = motorTorqueMultiplayer * strengthCoefficient * Time.deltaTime * inp.vertical;
                throttleWheels[i].motorTorque = horsePower * motorTorqueMultiplier * Time.deltaTime / 2;
                throttleWheels[i].brakeTorque = 0f;
            }
        }
        else
        {
            for (int i = 0; i < 2; i++)
            {
                //throttleWheels[i].motorTorque = motorTorqueMultiplayer * strengthCoefficient * Time.deltaTime * inp.vertical;
                throttleWheels[i].motorTorque = horsePower * motorTorqueMultiplier * Time.deltaTime / 2;
                throttleWheels[i].brakeTorque = 0f;
            }
        }

        //HANDLE BRAKING
        if (inp.handBrake)
        {
            foreach (WheelCollider wheel in throttleWheels)
            {
                wheel.motorTorque = 0f;
            }
            throttleWheels[2].brakeTorque = throttleWheels[3].brakeTorque = brakeStrength * brakeMultiplayer * Time.deltaTime;
        }

    }
    private void wheelsVertical()
    {
        if(inp.horizontal > 0)
        {
            //handle angle
            steerWheels[0].GetComponent<WheelCollider>().steerAngle = Mathf.Rad2Deg * Mathf.Atan(2.55f / (radius + (1.5f / 2))) + inp.horizontal;
            steerWheels[1].GetComponent<WheelCollider>().steerAngle = Mathf.Rad2Deg * Mathf.Atan(2.55f / (radius - (1.5f / 2))) + inp.horizontal;
            //handle animation, maybe correct this
            steerWheels[0].transform.localEulerAngles = new Vector3(0f, inp.horizontal * maxTurn, 0f);
            steerWheels[1].transform.localEulerAngles = new Vector3(0f, inp.horizontal * maxTurn, 0f);
           
          
        }
        else if(inp.horizontal < 0)
        {
            steerWheels[0].GetComponent<WheelCollider>().steerAngle = -Mathf.Rad2Deg * Mathf.Atan(2.55f / (radius - (1.5f / 2))) + inp.horizontal;
            steerWheels[1].GetComponent<WheelCollider>().steerAngle = -Mathf.Rad2Deg * Mathf.Atan(2.55f / (radius + (1.5f / 2))) + inp.horizontal;
            steerWheels[0].transform.localEulerAngles = new Vector3(0f, inp.horizontal * maxTurn, 0f);       
            steerWheels[1].transform.localEulerAngles = new Vector3(0f, inp.horizontal * maxTurn, 0f);
        }
        else
        {
            steerWheels[0].GetComponent<WheelCollider>().steerAngle = 0f;
            steerWheels[1].GetComponent<WheelCollider>().steerAngle = 0f;
            steerWheels[0].transform.localEulerAngles = new Vector3(0f, inp.horizontal * maxTurn, 0f);
            steerWheels[1].transform.localEulerAngles = new Vector3(0f, inp.horizontal * maxTurn, 0f);
        }
    }

    private void animateWheels()// handles rotation of the wheels
    {
        int counterRotate = 0;
        foreach (GameObject mesh in wheelMeshes)
        {
            if(inp.handBrake)
            {
                if(counterRotate == (int)wheelPos.BL || counterRotate == (int)wheelPos.BR)
                {
                    continue;
                }
            }

            if (counterRotate % 2 == 1)
            {
                mesh.transform.Rotate(RigBod.velocity.magnitude * (transform.InverseTransformDirection(RigBod.velocity).z >= 0 ? -1 : 1) / (2 * Mathf.PI * 0.3f), 0f, 0f);
            }
            else
            {
                mesh.transform.Rotate(RigBod.velocity.magnitude * (transform.InverseTransformDirection(RigBod.velocity).z >= 0 ? 1 : -1) / (2 * Mathf.PI * 0.3f), 0f, 0f);
            }

            counterRotate++;

        }
    }

    private void applyDownForce()
    {
        RigBod.AddForce(-transform.up * downForce * RigBod.velocity.magnitude);
    }

    private void getFriction()
    {
        for(int i=0; i<4; i++)
        {
            WheelHit wheelHit;
            throttleWheels[i].GetGroundHit(out wheelHit);
            forwardSlip[i] = wheelHit.forwardSlip;
            sidewaysSlip[i] = wheelHit.sidewaysSlip;
            motorTorque[i] = throttleWheels[i].motorTorque;

        }
        
    }

    private void calculateWheelsRPM()
    {
        float sum = 0;
        int R = 0;
       foreach(WheelCollider wheel in throttleWheels)
        {
            sum += wheel.rpm;
            R++;
        }
        wheelsRPM = (R != 0) ? sum / R : 0;

        if (wheelsRPM < -0.5)//bo niedlokladnosci sa 
            goingBackwards = true;
        else
            goingBackwards = false;
    }


    private void shiftGearsManual()
    {
        if (goingBackwards)
            return;

        if(inp.gearDown)
        {
            if (gearNum > 1 )
                gearNum--;
        }
        else if(inp.gearUp)
        {
            if(gearNum < totalGears)
                gearNum++;
        }
    }

    private void shiftGearsAutomatic()
    {
        if (goingBackwards)
            return;

        if (engineRPM > maxEngingeRPM && gearNum < totalGears)
        {  
            gearNum++;
        }
        else if(engineRPM < minEngingeRPM && gearNum > 1)
        {
            gearNum--;
        }
    }
    private void calculateEnginePower()
    {
        calculateWheelsRPM();

        horsePower = enginePower.Evaluate(engineRPM) * 3.6f * inp.vertical ;
        float velocity = 0f;
        engineRPM = Mathf.SmoothDamp(engineRPM, 1000 + (Mathf.Abs(wheelsRPM) * 3.6f * (gears[gearNum-1])), ref velocity, smoothTime);
    }


    private void nitrous()
    {
        if (!inp.nitro)
        {
            foreach(ParticleSystem particle in nitroParticles)
            {
                particle.Stop();
            }

            if(nitroLeft < nitroMax)
            nitroLeft += Time.deltaTime * nitroGain * RigBod.velocity.magnitude;
            return;
        }
        if(nitroLeft == 0)
        {
            foreach (ParticleSystem particle in nitroParticles)
            { 
                particle.Stop();
            }
            return;
        }

        foreach (ParticleSystem particle in nitroParticles)
        {
            particle.Play();
        }

        nitroLeft -= Time.deltaTime * nitroConsumption;

        if (nitroLeft < 0)
            nitroLeft = 0;

        RigBod.AddForce(RigBod.transform.forward * n2oThrust, ForceMode.Acceleration);



    }

   
}
