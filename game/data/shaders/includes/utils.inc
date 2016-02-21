
void outputGBuffer(vec3 albedo, vec3 normal, vec2 velocity)
{
    gl_FragData[0] = vec4(albedo, 1);
    gl_FragData[1] = vec4(v_normal, 1);
    gl_FragData[2] = vec4(velocity, 0, 1);
}