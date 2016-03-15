
void outputGBuffer(vec3 albedo, vec3 normal, vec3 gNormal, vec2 id, vec2 velocity)
{
    normal = normal / 2 + 0.5;
    gNormal = gNormal / 2 + 0.5;

    gl_FragData[0] = vec4(albedo, 1);
    gl_FragData[1] = vec4(normal, gNormal.z);
    gl_FragData[2] = vec4(id, gNormal.xy);   
    gl_FragData[3] = vec4(velocity * 10000, -1, -1);
}
