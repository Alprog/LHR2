
void outputGBuffer(vec3 albedo, vec3 normal, vec2 id, vec2 velocity)
{
    gl_FragData[0] = vec4(albedo, 1);
    gl_FragData[1] = vec4(normal / 2 + 0.5, 1);
    gl_FragData[2] = vec4(id, 0, 1);   
    gl_FragData[3] = vec4(velocity * 10000, -1, -1);
}
