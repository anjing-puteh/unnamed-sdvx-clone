#ifdef EMBEDDED
varying vec2 fsTex;
varying vec4 position;
#else
#extension GL_ARB_separate_shader_objects : enable
layout(location=1) in vec2 fsTex;
layout(location=0) out vec4 target;
in vec4 position;
#endif

uniform sampler2D mainTex;
uniform bool hasSample;


uniform float trackPos;
uniform float trackScale;
uniform float hiddenCutoff;
uniform float hiddenFadeWindow;
uniform float suddenCutoff;
uniform float suddenFadeWindow;

#ifdef EMBEDDED
void main()
{	
	vec4 mainColor = texture(mainTex, fsTex.xy);
    if(hasSample)
    {
        float addition = abs(0.5 - fsTex.x) * - 1.;
        addition += 0.2;
        addition = max(addition,0.);
        addition *= 2.8;
        mainColor.xyzw += addition;
    }

    target = mainColor;
}

#else
void main()
{	
	vec4 mainColor = texture(mainTex, fsTex.xy);
    if(hasSample)
    {
        float addition = abs(0.5 - fsTex.x) * - 1.;
        addition += 0.2;
        addition = max(addition,0.);
        addition *= 2.8;
        mainColor.xyzw += addition;
    }

    target = mainColor;
    
    float off = trackPos + position.y * trackScale;
    
    if(hiddenCutoff < suddenCutoff)
    {
        float hiddenCutoffFade = hiddenCutoff - hiddenFadeWindow;
        if (off < hiddenCutoff) {
            target = target * max(0.0, (off - hiddenCutoffFade) / hiddenFadeWindow);
        }

        float suddenCutoffFade = suddenCutoff + suddenFadeWindow;
        if (off > suddenCutoff) {
            target = target * max(0.0, (suddenCutoffFade - off) / suddenFadeWindow);
        }
    }
    else
    {
        float hiddenCutoffFade = hiddenCutoff + hiddenFadeWindow;
        if (off > hiddenCutoff) {
            target = target * clamp((off - hiddenCutoffFade) / hiddenFadeWindow, 0.0, 1.0);
        }

        float suddenCutoffFade = suddenCutoff - suddenFadeWindow;
        if (off < suddenCutoff) {
            target = target * clamp((suddenCutoffFade - off) / suddenFadeWindow, 0.0, 1.0);
        }

        if (off > suddenCutoff && off < hiddenCutoff) {
            target = target * vec4(0.0);
        }
    }
}
#endif