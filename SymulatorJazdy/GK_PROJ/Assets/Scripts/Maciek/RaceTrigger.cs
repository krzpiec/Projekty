using System;
using UnityEngine;

namespace Maciek
{
    public class RaceTrigger : MonoBehaviour
    {
        public event Action<RaceTrigger> OnSpecificTriggered;
        public event Action OnTriggered;

        private const string CarTag = "Player";        
    
        private void OnTriggerEnter(Collider other)
        {
            if (other.CompareTag(CarTag))
            {
                LaunchTrigger();
            }
        }

        private void LaunchTrigger()
        {
            OnSpecificTriggered?.Invoke(this);
            OnTriggered?.Invoke();
        }
    }
}