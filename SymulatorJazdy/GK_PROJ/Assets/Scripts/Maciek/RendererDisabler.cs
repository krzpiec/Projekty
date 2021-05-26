using UnityEngine;

namespace Maciek
{
    public class RendererDisabler : MonoBehaviour
    {
        private void Start()
        {
            GetComponent<Renderer>().enabled = false;
        }
    }
}