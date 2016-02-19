
void outputGBuffer(vec3 albedo, vec3 normal)
{
    gl_FragData[0] = vec4(albedo, 1);
    gl_FragData[1] = vec4(v_normal, 1);
    gl_FragData[2] = vec4(1, 0, 0, 1);
}