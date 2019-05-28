#version 400

in vec3 colour,position_eye, normal_eye;


uniform mat4 view;


out vec4 frag_colour;


//propriedades luz pontual
vec3 light_position_world = vec3(-4.0, 0.0, 4.0);
vec3 Ls = vec3(1.0, 1.0,1.0); // cor especular branca 
vec3 Ld = vec3(0.7, 0.7,0.7); // cor difusa acinzentado
vec3 La = vec3(0.2, 0.2,0.2); // cor ambiente cinza 

//propriedades superfice do obj
vec3 Ks = vec3(1.0, 1.0, 1.0); // reflete totalmente a luz //especular
vec3 Kd = vec3(colour); // reflexão difusa da cor 
vec3 Ka = vec3(1.0, 1.0, 1.0); // reflete totalmente a luz //ambiente 
float specular_exponent = 100.00; //potencia expecular


void main() {
	
	//intensidade ambiente
	vec3 Ia = La * Ka;

	//intensidade difusa
	//coord mundo -> coord view
	vec3 light_position= vec3 (view *vec4(light_position_world ,1.0));
	//direcao normal de superficie e luz
	vec3 distance_to_light= light_position - position_eye;
	vec3 direction_to_light= normalize (distance_to_light);
	// multiplica vetor normal pelo vetor da luz
	float dot_prod = dot(direction_to_light, normal_eye);
	dot_prod = max(dot_prod, 0.0); //evita valores negativos

	vec3 Id = Ld* Kd* dot_prod; // intensidade difusa final						
	//intensidade especular
	vec3 surface_to_viewer= normalize (-position_eye);
	// vetor de reflexão entre superfície e fonte de luz
	vec3 reflection= reflect(-direction_to_light, normal_eye);
	// multiplica vetor de reflexão pela direção da camera
	float dot_prod_specular= dot(reflection, surface_to_viewer);
	dot_prod_specular= max(dot_prod_specular, 0.0);
	//intensidade do efeito especular varia conforme expoente 	//especular
	float specular_factor= pow(dot_prod_specular, 	specular_exponent);

	vec3 Is = Ls * Ks * specular_factor; // intensidade 	//especular final
	
	frag_colour = vec4 (Ia + Id + Is, 1.0);

	//frag_colour = vec4 (colour, 1.0);
}
