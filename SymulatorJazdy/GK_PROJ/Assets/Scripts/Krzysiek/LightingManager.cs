using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LightingManager : MonoBehaviour
{
    public List<Light> frontLigts;
    public List<Light> brakeLigts;
    public virtual void ToggleHeadlights()
    {
        foreach(Light light in frontLigts)
        {
            light.intensity = light.intensity == 0 ? 2 : 0; 
        }
    }
    public virtual void HandleBreaklights(bool state)
    {
        foreach (Light light in brakeLigts)
        {
            
            light.intensity = state ? 7f : 0;
        }
    }
}
