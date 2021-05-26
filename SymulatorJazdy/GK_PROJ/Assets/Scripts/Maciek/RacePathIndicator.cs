using System;
using UnityEngine;

namespace Maciek
{
    public class RacePathIndicator : MonoBehaviour
    {
        private Renderer[] renderers;
        
        private void Awake()
        {
            renderers = GetComponentsInChildren<Renderer>();
        }

        private void Start()
        {
            GetComponentInParent<RaceController>().OnBegan += Show;
            GetComponent<RaceTrigger>().OnTriggered += Hide;
        }

        private void Show()
        {
            foreach (Renderer r in renderers)
            {
                r.enabled = true;
            }
        }

        private void Hide()
        {
            foreach (Renderer r in renderers)
            {
                r.enabled = false;
            }
        }
    }
}