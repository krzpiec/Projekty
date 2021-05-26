using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraContraption : MonoBehaviour
{
    // Start is called before the first frame update

    [Header("References")]
    public Transform trackedPosTransform;
    public Transform yawTarget;
    public Transform lookAtTransform;

    [Header("Fields")]
    public float posLerpSpeed=8;
    public float yawLerpSpeed = 8;
    public float lookAtLerpSpeed = 8;


    [Header("Dependencies")]

    [SerializeField] private Transform posTransform;
    [SerializeField] private Transform yawTransform;
    [SerializeField] private Transform cameraTransform;

    private void Awake()
    {
        if (posTransform == null) {
            Debug.LogWarning(nameof(posTransform) +" not referenced in " + nameof(CameraContraption));
        }

        if (yawTransform == null) {
            Debug.LogWarning(nameof(yawTransform) + " not referenced in " + nameof(CameraContraption));
        }

            if (cameraTransform == null)
        {
            Debug.LogWarning(nameof(cameraTransform) + " not referenced in " + nameof(CameraContraption));
        }
        else
        {
            if (cameraTransform.GetComponent<Camera>() == null) { 
                Debug.LogWarning(nameof(cameraTransform) + " has no component: " + nameof(Camera));
            }
        }

        



    }

    void Start()
    {
        
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        if (trackedPosTransform != null&& posTransform!=null) {
            posTransform.position = Vector3.Lerp(
                     posTransform.position,
                     trackedPosTransform.position,
                     Time.deltaTime * posLerpSpeed
                );
        }


        if (lookAtTransform != null&& cameraTransform!=null) {
            cameraTransform.rotation = Quaternion.Lerp(
                cameraTransform.rotation,
                Quaternion.LookRotation((lookAtTransform.position - cameraTransform.position), Vector3.up),
                Time.deltaTime * lookAtLerpSpeed);
        }


        if (yawTarget != null && yawTransform != null) {
            yawTransform.rotation = Quaternion.Lerp(
                yawTransform.rotation,
                yawTarget.rotation,
                Time.deltaTime * yawLerpSpeed);
        }





    }

    private void OnDrawGizmosSelected()
    {
        Gizmos.color = Color.magenta;
        Gizmos.DrawSphere(posTransform.position, 0.4f);
    }

}
