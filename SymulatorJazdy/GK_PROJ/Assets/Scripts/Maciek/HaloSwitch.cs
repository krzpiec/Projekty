using UnityEngine;
using UnityEngine.Events;

namespace Maciek
{
    public class HaloSwitch : MonoBehaviour
    {
        [SerializeField] private UnityEvent showEvent;
        [SerializeField] private UnityEvent hideEvent;
        
        private void Start()
        {
            GetComponentInParent<RaceController>().OnBegan += Show;
            GetComponent<RaceTrigger>().OnTriggered += Hide;
        }

        private void Show()
        {
            showEvent?.Invoke();
        }

        private void Hide()
        {
            hideEvent?.Invoke();
        }
    }
}