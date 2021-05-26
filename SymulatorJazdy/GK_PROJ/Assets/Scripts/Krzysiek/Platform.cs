using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Platform : MonoBehaviour
{
    public float rotationSpeed = 15f;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        transform.Rotate(new Vector3(0f, rotationSpeed * Time.deltaTime, 0f));
        GameObject.FindGameObjectWithTag("Player").transform.Rotate(new Vector3(0f, rotationSpeed * Time.deltaTime, 0f));
    }
}
