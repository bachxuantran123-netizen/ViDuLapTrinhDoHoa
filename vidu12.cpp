//
// Ky thuat do hoa
// Ha Manh Toan lhttuy@gmail.com
//
#include <time.h>
#include "texturemodel.h"
#include "imageloader.h"
#include "virtualreality.h"
using namespace hmtoan;

namespace vidu12 {
// =================== Models ===================
class ArmRobotModel {
public:
	VirtualObject* baseNode;
	VirtualObject* baseMesh;
	VirtualObject* shoulderNode;
	VirtualObject* shoulderMesh;
	VirtualObject* upperArmNode;
	VirtualObject* upperArmMesh;
	VirtualObject* forearmNode;
	VirtualObject* forearmMesh;
	VirtualObject* wristNode;
	VirtualObject* wristMesh;
	VirtualObject* gripLeft;
	VirtualObject* gripRight;
	SphereCollider* gripLeftCollider;
	SphereCollider* gripRightCollider;

	ArmRobotModel() {
		create();
	}

	void reset() {
		shoulderNode->transform.localRot.y = 0;
		upperArmNode->transform.localRot.z = 60;
		forearmNode->transform.localRot.z = 60;
		wristNode->transform.localRot.y = 0;
		gripLeft->transform.localPos.x = -0.5f;
		gripRight->transform.localPos.x = 0.5f;
	}

	void rotateShoulder(float v) {
		shoulderNode->transform.localRot.y += v;
	}
	void rotateUpperArm(float v) {
		upperArmNode->transform.localRot.z += v;
	}
	void rotateForearm(float v) {
		forearmNode->transform.localRot.z += v;
	}
	void rotateWrist(float v) {
		wristNode->transform.localRot.y += v;
	}
	void moveGrip(float v) {
		gripLeft->transform.localPos.x += v;
		gripRight->transform.localPos.x -= v;
	}
	void place(float x, float y, float z) {
		baseNode->transform.localPos = { x, y, z };
	}

	bool testTake(VirtualObject* target) {
		if (gripLeft->collider->intersects(target->collider) &&
			gripRight->collider->intersects(target->collider)) {
			return true;
		}
	}
	Vec3 gripPosition() {
		return 0.5 * (gripLeft->transform.getWorldPosition() + gripRight->transform.getWorldPosition());
	}
	const Vec3& getLocalPosition() {
		return baseNode->transform.localPos;
	}

	void create() {
		// Base
		baseNode = new VirtualObject();
		baseNode->transform.localPos = { 0, 0, 0 };

		baseMesh = new VirtualObject();
		baseMesh->transform.localPos = { 0, 0.25f, 0 };
		baseMesh->transform.localScale = { 2.0f, 0.5f, 2.0f };
		baseMesh->meshRenderer = new MeshRenderer();
		baseMesh->meshRenderer->mesh = createUnitCube();
		baseMesh->meshRenderer->texture = textureFromBMP("data/roof1.bmp");
		baseNode->addChild(baseMesh);

		// Shoulder
		shoulderNode = new VirtualObject();
		shoulderNode->transform.localPos = { 0, 0.5f, 0 };
		baseNode->addChild(shoulderNode);

		shoulderMesh = new VirtualObject();
		shoulderMesh->transform.localPos = { 0, 2.0f, 0 };
		shoulderMesh->transform.localScale = { 0.6f, 4.0f, 0.6f };
		shoulderMesh->meshRenderer = new MeshRenderer();
		shoulderMesh->meshRenderer->mesh = createUnitCube();
		shoulderMesh->meshRenderer->texture = textureFromBMP("data/sky.bmp");
		shoulderNode->addChild(shoulderMesh);

		// Upper arm
		upperArmNode = new VirtualObject();
		upperArmNode->transform.localPos = { 0, 4.0f, 0 };
		shoulderNode->addChild(upperArmNode);

		upperArmMesh = new VirtualObject();
		upperArmMesh->transform.localPos = { 0, 1.75f, 0 };
		upperArmMesh->transform.localScale = { 0.4f, 3.5f, 0.4f };
		upperArmMesh->meshRenderer = new MeshRenderer();
		upperArmMesh->meshRenderer->mesh = createUnitCube();
		upperArmMesh->meshRenderer->texture = textureFromBMP("data/roof.bmp");
		upperArmNode->addChild(upperArmMesh);

		// Forearm
		forearmNode = new VirtualObject();
		forearmNode->transform.localPos = { 0, 3.5f, 0 };
		upperArmNode->addChild(forearmNode);

		forearmMesh = new VirtualObject();
		forearmMesh->transform.localPos = { 0, 1.25f, 0 };
		forearmMesh->transform.localScale = { 0.35f, 2.5f, 0.35f };
		forearmMesh->meshRenderer = new MeshRenderer();
		forearmMesh->meshRenderer->mesh = createUnitCube();
		forearmMesh->meshRenderer->texture = textureFromBMP("data/window.bmp");
		forearmNode->addChild(forearmMesh);

		// Wrist
		wristNode = new VirtualObject();
		wristNode->transform.localPos = { 0, 2.5f, 0 };
		forearmNode->addChild(wristNode);

		wristMesh = new VirtualObject();
		wristMesh->transform.localPos = { 0, 0.2f, 0 };
		wristMesh->transform.localScale = { 1.f, 0.4f, 0.3f };
		wristMesh->meshRenderer = new MeshRenderer();
		wristMesh->meshRenderer->mesh = createUnitCube();
		wristMesh->meshRenderer->texture = textureFromBMP("data/skytop.bmp");
		wristNode->addChild(wristMesh);

		// Gripper left
		gripLeft = new VirtualObject();
		gripLeft->transform.localPos = { -0.5f, 0.4f, 0 };
		gripLeft->transform.localScale = { 0.1f, 0.4f, 0.1f };
		gripLeft->meshRenderer = new MeshRenderer();
		gripLeft->meshRenderer->mesh = createUnitCube();
		gripLeft->meshRenderer->texture = textureFromBMP("data/b.bmp");
		wristNode->addChild(gripLeft);

		// Gripper right
		gripRight = new VirtualObject();
		gripRight->transform.localPos = { 0.5f, 0.4f, 0 };
		gripRight->transform.localScale = { 0.1f, 0.4f, 0.1f };
		gripRight->meshRenderer = new MeshRenderer();
		gripRight->meshRenderer->mesh = createUnitCube();
		gripRight->meshRenderer->texture = textureFromBMP("data/b.bmp");
		wristNode->addChild(gripRight);

		gripLeftCollider = new SphereCollider(0.2f);
		gripLeftCollider->transform = &gripLeft->transform;
		gripLeft->collider = gripLeftCollider;

		gripRightCollider = new SphereCollider(0.2f);
		gripRightCollider->transform = &gripRight->transform;
		gripRight->collider = gripRightCollider;

		reset();
	}
};

class TargetModel {
public:
	VirtualObject* targetSphere;
	Collider* targetCollider;


	TargetModel() {
		create();
	}
	void place(float x, float y, float z) {
		targetSphere->transform.localPos = { x, y, z };
	}
	void create() {
		targetSphere = new VirtualObject();
		targetSphere->transform.localPos = { 0.8f, 0.25f, -2.0f };
		targetSphere->transform.localScale = { 0.5f, 0.5f, 0.5f };
		targetSphere->meshRenderer = new MeshRenderer();
		targetSphere->meshRenderer->mesh = createUnitSphere();
		targetSphere->meshRenderer->texture = textureFromBMP("data/sky.bmp");

		targetCollider = new SphereCollider(0.5f);
		targetCollider->transform = &targetSphere->transform;
		targetSphere->collider = targetCollider;
	}
};

// =================== Controls ===================
struct ArmRobotState {
	float shoulderYAngle;
	float upperArmZAngle;
	float forearmZAngle;
	float wristYAngle;
	float gripLeftX;
	float gripRightX;
};
struct TargetState {
	float x, y, z;
};
struct State {
	ArmRobotState armRobotState;
	TargetState targetState;
};
struct Action {
	float dShoulderYAngle;
	float dUpperArmZAngle;
	float dForearmZAngle;
	float dWristYAngle;
	float dMoveGrip;
};
class ArmRobot : public Actor {
public:
	ArmRobotModel* model = nullptr;

	void reset() override {
		model->reset();
	}

	Vec3 getCheckpoint() {
		return model->gripPosition();
	}

	void applyAction(const Action& a, float dt) {
		model->rotateForearm(a.dForearmZAngle * dt);
		model->rotateShoulder(a.dShoulderYAngle * dt);
		model->rotateUpperArm(a.dUpperArmZAngle * dt);
		model->rotateWrist(a.dWristYAngle * dt);
		model->moveGrip(a.dMoveGrip * dt);
	}

	ArmRobotState getState() {
		ArmRobotState state;
		state.shoulderYAngle = model->shoulderNode->transform.localRot.y;
		state.upperArmZAngle = model->upperArmNode->transform.localRot.z;
		state.forearmZAngle = model->forearmNode->transform.localRot.z;
		state.wristYAngle = model->wristNode->transform.localRot.y;
		state.gripLeftX = model->gripLeft->transform.localPos.x;
		state.gripRightX = model->gripRight->transform.localPos.x;
		return state;
	}
};
class Target : public Actor {
public:
	TargetModel* model = nullptr;

	Vec3 center;
	float minRadius, maxRadius;

	void reset() override {
		float angle = 1.0 * rand() / RAND_MAX * 2 * PI;
		float radius = 1.0 * rand() / RAND_MAX * (maxRadius - minRadius) + minRadius;
		float x = cos(angle) * radius;
		float z = sin(angle) * radius;
		//printf("target %f %f %f\n", center.x+x, center.y, center.z+z);
		model->place(center.x + x, center.y, center.z + z);
	}
	void init(Vec3 center, float minRadius, float maxRadius) {
		this->center = center;
		this->minRadius = minRadius;
		this->maxRadius = maxRadius;
	}

	Vec3 getDestination() {
		return model->targetSphere->transform.getWorldPosition();;
	}
	TargetState getState() {
		TargetState state;
		state.x = model->targetSphere->transform.localPos.x;
		state.y = model->targetSphere->transform.localPos.y;
		state.z = model->targetSphere->transform.localPos.z;
		return state;
	}
};

struct StepResult {
	State observation;
	float reward;
	bool done;
};

class SimpleReachEnv {
public:
	SimpleReachEnv(ArmRobot* r, Target* t) {
		robot = r;
		target = t;
		reset();
	}

	State reset() {
		robot->reset();
		target->reset();
		syncState();
		return state;
	}

	StepResult step(const Action& a) {
		robot->applyAction(a, dt);
		syncState();

		StepResult r;
		r.observation = state;
		Vec3 A = robot->getCheckpoint();
		Vec3 B = target->getDestination();
		//printf("A %f %f %f B %f %f %f\n", A.x, A.y, A.z, B.x, B.y, B.z);
		r.reward = -length(A - B);
		r.done = r.reward > -0.1f; // chua xet va cham that
		return r;
	}
private:
	ArmRobot* robot = nullptr;
	Target* target = nullptr;
	State state;
	void syncState() {
		state.armRobotState = robot->getState();
		state.targetState = target->getState();
	}
	const float dt = 0.05f;
};

class InputManager {
public:
	Action action;
	const float v = 0.01f;

	void keyDown(unsigned char key) {
		if (key == 'w') action.dForearmZAngle += v;
		if (key == 's') action.dForearmZAngle -= v;
		if (key == 'a') action.dUpperArmZAngle += v;
		if (key == 'd') action.dUpperArmZAngle -= v;
		if (key == 'q') action.dShoulderYAngle += v;
		if (key == 'e') action.dShoulderYAngle -= v;
		if (key == 'o') action.dWristYAngle += v;
		if (key == 'p') action.dWristYAngle -= v;
		if (key == 'k') action.dMoveGrip += v;
		if (key == 'l') action.dMoveGrip -= v;
	}

	void keyUp(unsigned char) {
		action = Action(); // reset
	}
};

// =================== Light ===================
void setupLight() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat diffuse[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };

	GLfloat position[] = { 10.0f, 10.0f, 10.0f, 1.0f }; // point light

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}


// =================== Scene ===================
class Scene {
public:
	std::vector<Actor*> actors;
	VirtualObject* root = nullptr;
	CameraObject* mainCamera;

	VirtualObject* ground = nullptr;
	ArmRobotModel* armRobotModel = nullptr;
	TargetModel* targetModel = nullptr;

	void create() {
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);

		setupLight();

		root = new VirtualObject();

		mainCamera = new CameraObject();
		mainCamera->setController(new OrbitCameraController());
		((OrbitCameraController*)mainCamera->controller)->lookAt(Vec3(10, 10, 10), Vec3(0, 0, 0));
		root->addChild(mainCamera);

		ground = new VirtualObject();
		ground->transform.localPos = { 0,0,0 };
		ground->meshRenderer = new MeshRenderer();
		ground->meshRenderer->mesh = createGridPlane();
		ground->meshRenderer->texture = textureFromBMP("data/grass.bmp");
		root->addChild(ground);

		armRobotModel = new ArmRobotModel();
		armRobotModel->place(0, 0.4f, 0);
		root->addChild(armRobotModel->baseNode);

		targetModel = new TargetModel();
		root->addChild(targetModel->targetSphere);
	}
	void update(float dt = -1.f) {
		for (auto a : actors)
			a->update(dt);

		root->transform.updateWorld();
	}
	void render() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mainCamera->camera.applyView();
		renderObject(root);

		glutSwapBuffers();
	}
};
Scene* scene;
ArmRobot* robot;
Target* target;

SimpleReachEnv* env;
InputManager* input;

void init() {
	srand(time(0));
	scene = new Scene();
	scene->create();

	robot = new ArmRobot();
	robot->model = scene->armRobotModel;
	scene->actors.push_back(robot);

	target = new Target();
	target->model = scene->targetModel;
	target->init(robot->model->getLocalPosition(), 2.2f, 3.5f);

	env = new SimpleReachEnv(robot, target);
	input = new InputManager();

}

// =================== Callbacks ===================
void mouseButton(int b, int s, int x, int y) {
	scene->mainCamera->controller->onMouseButton(b, s, x, y);
}
void mouseMove(int x, int y) {
	scene->mainCamera->controller->onMouseMove(x, y);
}
void keyboardDown(unsigned char key, int, int) {
	input->keyDown(key);
}
void keyboardUp(unsigned char key, int, int) {
	input->keyUp(key);
}
void display() {
	auto p = scene->targetModel->targetSphere->transform.getWorldPosition();
	//printf("target %f %f %f\n", p.x, p.y, p.z);
	auto p1 = scene->armRobotModel->baseNode->transform.getWorldPosition();
	//printf("armRobot %f %f %f\n", p1.x, p1.y, p1.z);
	scene->render();
}
void idle() {
	StepResult result = env->step(input->action);
	if (result.done) {
		env->reset();
	}

	scene->update();

	glutPostRedisplay();
}
// =================== Main ===================
int main(int argc, char** argv) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("vidu12");

	init();

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	glutMainLoop();
	return 0;
}

}