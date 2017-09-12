xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header {
 1;
 0;
 1;
}

Mesh Model {
 32;
 -0.116500;-0.061100;0.057300;,
 -1.866500;-0.061100;0.057300;,
 -1.866500;-0.061100;-0.067700;,
 -0.116500;-0.061100;-0.067700;,
 -0.116500;0.063900;0.057300;,
 -0.116500;0.063900;-0.067700;,
 -1.866500;0.063900;-0.067700;,
 -1.866500;0.063900;0.057300;,
 -0.116500;-0.061100;0.057300;,
 -0.116500;-0.061100;-0.067700;,
 -0.116500;0.063900;-0.067700;,
 -0.116500;0.063900;0.057300;,
 -1.866500;-0.061100;-0.067700;,
 -0.116500;0.063900;-0.067700;,
 -1.866500;-0.061100;-0.067700;,
 -1.866500;-0.061100;0.057300;,
 -1.866500;0.063900;0.057300;,
 -1.866500;0.063900;-0.067700;,
 -1.866500;-0.061100;0.057300;,
 -0.116500;0.063900;0.057300;,
 0.179000;-0.001800;0.005600;,
 -0.121000;-0.151800;0.155600;,
 -0.121000;-0.151800;-0.144400;,
 -0.121000;-0.151800;-0.144400;,
 -0.121000;0.148200;-0.144400;,
 -0.121000;0.148200;-0.144400;,
 -0.121000;0.148200;0.155600;,
 -0.121000;0.148200;0.155600;,
 -0.121000;-0.151800;0.155600;,
 -0.121000;-0.151800;0.155600;,
 -0.121000;-0.001800;0.005600;,
 -0.121000;-0.151800;-0.144400;;

 20;
 3;0,1,2;,
 3;2,3,0;,
 3;4,5,6;,
 3;6,7,4;,
 3;8,9,10;,
 3;10,11,8;,
 3;3,12,6;,
 3;6,13,3;,
 3;14,15,16;,
 3;16,17,14;,
 3;18,0,19;,
 3;19,7,18;,
 3;20,21,22;,
 3;20,23,24;,
 3;20,25,26;,
 3;20,27,28;,
 3;29,30,31;,
 3;31,30,24;,
 3;24,30,27;,
 3;27,30,29;;

MeshMaterialList {
  2;
  20;
  0;,
  0;,
  0;,
  0;,
  0;,
  0;,
  0;,
  0;,
  0;,
  0;,
  0;,
  0;,
  1;,
  1;,
  1;,
  1;,
  1;,
  1;,
  1;,
  1;;
  Material {
   0.109800;0.109800;0.694100;1.000000;;
   32.00000;
   0.350000;0.350000;0.350000;;
   0.250000;0.250000;0.250000;;
  }
  Material {
   0.345100;0.780400;0.882400;1.000000;;
   32.00000;
   0.350000;0.350000;0.350000;;
   0.250000;0.250000;0.250000;;
  }
 }

 MeshTextureCoords {
  32;
  1.000000;0.000000;;
  1.000000;1.000000;;
  0.000000;1.000000;;
  0.000000;0.000000;;
  0.000000;0.000000;;
  1.000000;0.000000;;
  1.000000;1.000000;;
  0.000000;1.000000;;
  0.000000;0.000000;;
  1.000000;0.000000;;
  1.000000;1.000000;;
  0.000000;1.000000;;
  1.000000;0.000000;;
  0.000000;1.000000;;
  0.000000;0.000000;;
  1.000000;0.000000;;
  1.000000;1.000000;;
  0.000000;1.000000;;
  0.000000;0.000000;;
  1.000000;1.000000;;
  0.500000;1.000000;;
  0.000000;0.000000;;
  1.000000;0.000000;;
  0.000000;0.000000;;
  1.000000;0.000000;;
  0.000000;0.000000;;
  1.000000;0.000000;;
  0.000000;0.000000;;
  1.000000;0.000000;;
  0.000000;1.000000;;
  0.500000;0.500000;;
  1.000000;1.000000;,
}
}
