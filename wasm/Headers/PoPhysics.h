struct Physics
{
	void __forceinline Update(Object *object)
	{
		object->position.Translate(object->velocity.x, object->velocity.y, object->velocity.z);
		object->rotation.RotateX(object->angularvelocity.x);
		object->rotation.RotateY(object->angularvelocity.y);
		object->rotation.RotateZ(object->angularvelocity.z);

		if (object->velocity.x > +object->drag)object->velocity.x = object->velocity.x - (object->drag * (object->velocity.x * object->velocity.x));
		else if (object->velocity.x < -object->drag)object->velocity.x = object->velocity.x + (object->drag * (object->velocity.x * object->velocity.x));
		else object->velocity.x = 0;
		if (object->velocity.y > +object->drag)object->velocity.y = object->velocity.y - (object->drag * (object->velocity.y * object->velocity.y));
		else if (object->velocity.y < -object->drag)object->velocity.y = object->velocity.y + (object->drag * (object->velocity.y * object->velocity.y));
		else object->velocity.y = 0;
		if (object->velocity.z > +object->drag)object->velocity.z = object->velocity.z - (object->drag * (object->velocity.z * object->velocity.z));
		else if (object->velocity.z < -object->drag)object->velocity.z = object->velocity.z + (object->drag * (object->velocity.z * object->velocity.z));
		else object->velocity.z = 0;

		if (object->angularvelocity.x > +object->drag)object->angularvelocity.x = object->angularvelocity.x - (object->drag * (object->angularvelocity.x * object->angularvelocity.x));
		else if (object->angularvelocity.x < -object->drag)object->angularvelocity.x = object->angularvelocity.x + (object->drag * (object->angularvelocity.x * object->angularvelocity.x));
		else object->angularvelocity.x = 0;
		if (object->angularvelocity.y > +object->drag)object->angularvelocity.y = object->angularvelocity.y - (object->drag * (object->angularvelocity.y * object->angularvelocity.y));
		else if (object->angularvelocity.y < -object->drag)object->angularvelocity.y = object->angularvelocity.y + (object->drag * (object->angularvelocity.y * object->angularvelocity.y));
		else object->angularvelocity.y = 0;
		if (object->angularvelocity.z > +object->drag)object->angularvelocity.z = object->angularvelocity.z - (object->drag * (object->angularvelocity.z * object->angularvelocity.z));
		else if (object->angularvelocity.z < -object->drag)object->angularvelocity.z = object->angularvelocity.z + (object->drag * (object->angularvelocity.z * object->angularvelocity.z));
		else object->angularvelocity.z = 0;
	}
	void			   AddCollisionSphere(Object *object,float x, float y, float z, float r)
	{
		Object::CollisionSphere *collisionspherenew = new Object::CollisionSphere[object->collisionspherecount + 1];
		memcpy(collisionspherenew, object->collisionsphere, sizeof(Object::CollisionSphere)*object->collisionspherecount);
		collisionspherenew[object->collisionspherecount].position = float3(x, y, z);
		collisionspherenew[object->collisionspherecount].radius = r;
		delete object->collisionsphere;
		object->collisionsphere = collisionspherenew;
		object->collisionspherecount++;
	}
	void			   RemoveCollisionSphere(Object *object, UINT32 collisionsphereindex)
	{
		for (UINT32 s = collisionsphereindex;; s++)
		{
			if (s + 1 >= object->collisionspherecount)
			{
				object->collisionsphere[s] = Object::CollisionSphere();
				object->collisionspherecount--;
				return;
			}
			object->collisionsphere[s] = object->collisionsphere[s + 1];
		}
	}
	void __forceinline CollisionUpdate(Object *object0, Object *object1)
	{
		float numberofcollisions = 0;

		float3 initialprecollisionvelocity0 = object0->velocity;
		float3 initialprecollisionvelocity1 = object1->velocity;
		float3 initialprecollisionangularvelocity0 = object0->angularvelocity;
		float3 initialprecollisionangularvelocity1 = object1->angularvelocity;

		float3 collisionpositionvector0(0, 0, 0);
		float3 collisionpositionvector1(0, 0, 0);
		float3 collisionnormalvector0(0, 0, 0);
		float3 collisionnormalvector1(0, 0, 0);

		for (UINT32 i = 0; i < object0->collisionspherecount; i++)
		{
			for (UINT32 j = 0; j < object1->collisionspherecount; j++)
			{
				Matrix computationmatrix(4, 4);
				float4 transformedposition;
				computationmatrix.Identity();
				computationmatrix = computationmatrix * object0->rotation;
				computationmatrix = computationmatrix * object0->position;
				transformedposition = float4(object0->collisionsphere[i].position.x, object0->collisionsphere[i].position.y, object0->collisionsphere[i].position.z, 1) * computationmatrix;
				float3 collisionsphereposition0 = float3(transformedposition.x, transformedposition.y, transformedposition.z);
				computationmatrix.Identity();
				computationmatrix = computationmatrix * object1->rotation;
				computationmatrix = computationmatrix * object1->position;
				transformedposition = float4(object1->collisionsphere[j].position.x, object1->collisionsphere[j].position.y, object1->collisionsphere[j].position.z, 1) * computationmatrix;
				float3 collisionsphereposition1 = float3(transformedposition.x, transformedposition.y, transformedposition.z);

				if ((DistanceSquared(&collisionsphereposition0, &collisionsphereposition1)) < ((object0->collisionsphere[i].radius + object1->collisionsphere[j].radius)*(object0->collisionsphere[i].radius + object1->collisionsphere[j].radius)))
				{
					float3 currentcollisionnormalvector0(0, 0, 0);
					float3 currentcollisionnormalvector1(0, 0, 0);

					currentcollisionnormalvector0 = collisionsphereposition0 - collisionsphereposition1;
					currentcollisionnormalvector1 = collisionsphereposition1 - collisionsphereposition0;
					collisionnormalvector0 = collisionnormalvector0 + currentcollisionnormalvector0;
					collisionnormalvector1 = collisionnormalvector1 + currentcollisionnormalvector1;
					currentcollisionnormalvector0.Normalize();
					currentcollisionnormalvector1.Normalize();
					collisionpositionvector0 = collisionpositionvector0 + object0->collisionsphere[i].position - (currentcollisionnormalvector0 * object0->collisionsphere[i].radius);
					collisionpositionvector1 = collisionpositionvector1 + object1->collisionsphere[j].position - (currentcollisionnormalvector1 * object1->collisionsphere[j].radius);

					numberofcollisions++;
				}
			}
		}
		if (numberofcollisions)
		{
			collisionpositionvector0 = collisionpositionvector0 / numberofcollisions;
			collisionpositionvector1 = collisionpositionvector1 / numberofcollisions;
			collisionnormalvector0.Normalize();
			collisionnormalvector1.Normalize();

			float impulse;
			impulse = -(1 + (object0->restitution + object1->restitution) / 2) * (((initialprecollisionvelocity0 + (initialprecollisionangularvelocity0 ^  collisionpositionvector0)) - (initialprecollisionvelocity1 + (initialprecollisionangularvelocity1 ^  collisionpositionvector1))) * collisionnormalvector0);
			impulse = impulse / ((1 / object0->mass) + (1 / object1->mass) + (((collisionpositionvector0 ^ collisionnormalvector0)*(collisionpositionvector0 ^ collisionnormalvector0)) / object0->momentofinertia) + (((collisionpositionvector1 ^ collisionnormalvector0)*(collisionpositionvector1 ^ collisionnormalvector0)) / object1->momentofinertia));

			object0->velocity = object0->velocity + ((collisionnormalvector0*impulse) / object0->mass);
			object1->velocity = object1->velocity + ((collisionnormalvector1*impulse) / object1->mass);
			object0->angularvelocity = object0->angularvelocity - (((collisionpositionvector0 ^ collisionnormalvector0)*-impulse) / object0->momentofinertia);
			object1->angularvelocity = object1->angularvelocity - (((collisionpositionvector1 ^ collisionnormalvector1)*-impulse) / object1->momentofinertia);
		}
	}
	void __forceinline FloorCollisionUpdate(Object *object, float _floorheight, float  floorrestitution)
	{
		float numberofcollisions = 0;

		float3 initialprecollisionvelocity = object->velocity;
		float3 initialprecollisionangularvelocity = object->angularvelocity;

		float3 collisionpositionvector(0, 0, 0);
		float3 collisionnormalvector(0, 0, 0);

		for (UINT32 i = 0; i < object->collisionspherecount; i++)
		{
			Matrix computationmatrix(4, 4);
			float4 transformedposition;
			computationmatrix.Identity();
			computationmatrix = computationmatrix * object->rotation;
			computationmatrix = computationmatrix * object->position;
			transformedposition = float4(object->collisionsphere[i].position.x, object->collisionsphere[i].position.y, object->collisionsphere[i].position.z, 1) * computationmatrix;
			float3 collisionsphereposition0 = float3(transformedposition.x, transformedposition.y, transformedposition.z);

			float4 position4(0, 0, 0, 1); position4 = position4 * object->position;
			if (position4.y + object->collisionsphere[i].position.y - object->collisionsphere[i].radius <= _floorheight)
			{
				float3 currentcollisionnormalvector(0, 0, 0);

				currentcollisionnormalvector = float3(0,1,0);
				collisionnormalvector = collisionnormalvector + currentcollisionnormalvector;
				currentcollisionnormalvector.Normalize();
				collisionpositionvector = collisionpositionvector + object->collisionsphere[i].position - (currentcollisionnormalvector * object->collisionsphere[i].radius);
				numberofcollisions++;
			}
		}
		if (numberofcollisions)
		{
			collisionpositionvector = collisionpositionvector / numberofcollisions;
			collisionnormalvector.Normalize();

			float impulse;
			impulse = -(1 + floorrestitution) * (((initialprecollisionvelocity + (initialprecollisionangularvelocity ^  collisionpositionvector))) * collisionnormalvector);
			impulse = impulse / ((1 / object->mass) + (((collisionpositionvector ^ collisionnormalvector)*(collisionpositionvector ^ collisionnormalvector)) / object->momentofinertia));

			object->velocity = object->velocity + ((collisionnormalvector*impulse) / object->mass);
			object->angularvelocity = object->angularvelocity - (((collisionpositionvector ^ collisionnormalvector)*+impulse) / object->momentofinertia);
		}
	}
	void __forceinline Position(Object *object,float3 _position)
	{
		object->position.Identity();
		object->position.Translate(_position.x, _position.y, _position.z);
	}
	void __forceinline Rotation(Object *object, float3 _rotation)
	{
		object->rotation.Identity();
		object->rotation.RotateX(_rotation.x);
		object->rotation.RotateY(_rotation.y);
		object->rotation.RotateZ(_rotation.z);
	}
	void __forceinline MoveObject(Object *object, float3 _translate, float3 _rotate)
	{
		object->position.Translate(_translate.x, _translate.y, _translate.z);
		object->rotation.RotateX(_rotate.x);
		object->rotation.RotateX(_rotate.y);
		object->rotation.RotateX(_rotate.z);
	}
	void __forceinline Velocity(Object *object, float3 _velocity)
	{
		object->velocity = object->velocity + _velocity;
	}
	void __forceinline AngularVelocity(Object *object, float3 _angularvelocity)
	{
		object->angularvelocity = object->angularvelocity + _angularvelocity;
	}
	void __forceinline Force(Object *object, float3 _force)
	{
		object->velocity = object->velocity + (_force / object->mass);
	}
	void __forceinline Torque(Object *object, float3 _torque)
	{
		object->angularvelocity = object->angularvelocity + (_torque / object->momentofinertia);
	}
	void __forceinline Steer(Object *object, float3 _steer)
	{
		float4 forwardvector(0, 0, 1, 1);
		float4 upvector(0, 1, 0, 1);
		float4 rightvector(1, 0, 0, 1);
		forwardvector = forwardvector * object->rotation;
		upvector = upvector * object->rotation;
		rightvector = rightvector * object->rotation;

		object->rotation.Rotate(rightvector.x, rightvector.y, rightvector.z, _steer.x);
		object->rotation.Rotate(forwardvector.x, forwardvector.y, forwardvector.z, _steer.z);
		object->rotation.Rotate(upvector.x, upvector.y, upvector.z, _steer.y);

		float4 velocity4; velocity4 = float4(object->velocity.x, object->velocity.y, object->velocity.z, 1);
		Matrix velocitytransformationmatrix(4, 4);
		velocitytransformationmatrix.Identity();
		velocitytransformationmatrix.Rotate(rightvector.x, rightvector.y, rightvector.z, _steer.x);
		velocitytransformationmatrix.Rotate(forwardvector.x, forwardvector.y, forwardvector.z, _steer.z);
		velocitytransformationmatrix.Rotate(upvector.x, upvector.y, upvector.z, _steer.y);
		velocity4 = velocity4 * velocitytransformationmatrix;
		object->velocity = float3(velocity4.x, velocity4.y, velocity4.z);

		//object->velocity.Rotate(rightvector.x, rightvector.y, rightvector.z, _steer.x);
		//object->velocity.Rotate(forwardvector.x, forwardvector.y, forwardvector.z, _steer.z);
		//object->velocity.Rotate(upvector.x, upvector.y, upvector.z, _steer.y);

		//float4 rightvector = float4(1, 0, 0, 1);
		//float4 upvector4 = float4(0, 1, 0, 1);
		//float4 forwardvector4 = float4(0, 0, 1, 1);
		//Matrix forwardandupvectortransformationmatrix(4, 4);
		//forwardandupvectortransformationmatrix.Identity();
		//forwardandupvectortransformationmatrix.RotateX(object->rotation.x);
		//forwardandupvectortransformationmatrix.RotateY(object->rotation.y);
		//forwardandupvectortransformationmatrix.RotateZ(object->rotation.z);
		//rightvector = rightvector * forwardandupvectortransformationmatrix;
		//upvector4 = upvector4 * forwardandupvectortransformationmatrix;
		//forwardvector4 = forwardvector4 * forwardandupvectortransformationmatrix;

		////_steer = _steer * PI / 180;

		//float4 velocityvector = float4(object->velocity.x, object->velocity.y, object->velocity.z, 1);
		//float4 rotationvector = float4(object->rotation.x, object->rotation.y, object->rotation.z, 1);
		//Matrix velocityvectortransformationmatrix(4, 4);
		//velocityvectortransformationmatrix.Identity();
		//velocityvectortransformationmatrix.Rotate(rightvector.x, rightvector.y, rightvector.z, -_steer.x);
		//velocityvector = velocityvector * velocityvectortransformationmatrix;
		//rotationvector = rotationvector * velocityvectortransformationmatrix;
		//velocityvectortransformationmatrix.Identity();
		//velocityvectortransformationmatrix.Rotate(forwardvector4.x, forwardvector4.y, forwardvector4.z, -_steer.z);
		//velocityvector = velocityvector * velocityvectortransformationmatrix;
		//rotationvector = rotationvector * velocityvectortransformationmatrix;
		//object->velocity = float3(velocityvector.x, velocityvector.y, velocityvector.z);
		//object->rotation = float3(rotationvector.x, rotationvector.y, rotationvector.z);		
	}
};