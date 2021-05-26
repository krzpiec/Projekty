using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RadialCameraRig : MonoBehaviour
{
    // Start is called before the first frame update

    [Header("Fields")]
    public float innerRadius = 3;
    public bool freezeYAxis=true;



    [Header("References")]
    public Transform transformToTrack;



    [Header("Depenencies")]
    [SerializeField]private Transform tracker;




    private void Awake()
    {
        if (tracker == null) {
            enabled = false;
            Debug.LogWarning(nameof(RadialCameraRig) + " Won't work properly without " + nameof(tracker) + " asigned. Disabling the component");
        }
        
    }
    // Update is called once per frame
    void FixedUpdate()
    {


        if (transformToTrack == null) return;


        tracker.position = transformToTrack.position;
        if (freezeYAxis) {
            tracker.position = new Vector3(
                    tracker.position.x,
                    transform.position.y,
                    tracker.position.z
                );


        }

        float sqMag = Vector3.SqrMagnitude(tracker.localPosition);
        if (sqMag < innerRadius * innerRadius ) {

            tracker.localPosition = tracker.localPosition * innerRadius / tracker.localPosition.magnitude;

        }

        tracker.rotation = Quaternion.LookRotation(transform.position - tracker.position, Vector3.up);



    }
    private void OnDrawGizmosSelected()
    {
        Gizmos.color = Color.blue;

        Gizmos.DrawWireSphere(transform.position, innerRadius);
        Gizmos.DrawSphere(tracker.position, 0.5f);


    }


}
