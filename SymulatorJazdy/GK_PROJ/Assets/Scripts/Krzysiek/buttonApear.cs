using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class buttonApear : MonoBehaviour
{
    public Vector3 desiredPosition;
    public Vector3 startPosition;
    public bool flag;
    void Start()
    {
        flag = this.isActiveAndEnabled;
    }

    // Update is called once per frame
    void Update()
    {

        //Debug.Log(this.gameObject.transform.position);
        if (this.gameObject.activeSelf)
        {
            this.gameObject.transform.position = Vector3.Lerp(this.transform.position, desiredPosition, 0.005f);
        }
        else
        {
            this.gameObject.transform.position = startPosition;
        }

        Debug.Log(this.gameObject.activeInHierarchy);
    }
}
