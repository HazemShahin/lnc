#version 410

uniform sampler2D gridSampler;
uniform vec2 paintPos;
uniform float brushSize;
uniform int paintState;

in vec2 tc;
out vec3 FragColor;

void main() {
  vec2 texSize = vec2(textureSize(gridSampler,0));
  
  switch (paintState) {
    case 0 : {
      vec2 pixOffset[8] = vec2[]( vec2(-1,-1), vec2(0,-1), vec2(1,-1),
                                  vec2(-1, 0),             vec2(1, 0),
                                  vec2(-1, 1), vec2(0, 1), vec2(1, 1));
      
      float n = 0;
      float newGene = 0;
      for (int i = 0;i<8;i++) {
        n += (texture(gridSampler, tc + pixOffset[i] / texSize).r) > 0 ? 1 : 0;
        newGene += texture(gridSampler, tc + pixOffset[i] / texSize).r;
      }
      if(n>0)newGene/=n;

      vec3 gridValue = texture(gridSampler, tc).rgb;
      float age = gridValue.b;

      float result;
      if (gridValue.r > 0) {
        result = n == 2.0 || n == 3.0 ? gridValue.r : 0.0;
      } else {
        result = n == 3.0 ? newGene : 0.0;
      }
      age = age + (result==0 ? -1.0/256.0 : 2.0/256.0);
      
      float paintValue = (length(tc-paintPos) <= brushSize/texSize.x) ? 1.0 : 0.0;
      FragColor = vec3(result, paintValue, age);
      break;
    }
    case 1 : {
      vec3 gridValue = texture(gridSampler, tc).rgb;
      if (length(tc-paintPos) <= brushSize/texSize.x) {
        gridValue.r = 0.4;
      }
      gridValue.g = 0.0;
      FragColor = gridValue;
      break;
    }
  }
}
