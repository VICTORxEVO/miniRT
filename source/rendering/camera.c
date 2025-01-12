#include "miniRT.h"

t_vector	generate_cam_dir(t_camera	*cam, float scale, float ndcx, float ndcy)
{
	t_vector	dir;

	dir = cam->forward;
	dir.x += (ndcx * scale * cam->aspect * cam->right.x) + (ndcy * scale * cam->up.x);
	dir.y += (ndcx * scale * cam->aspect * cam->right.y) + (ndcy * scale * cam->up.y);
	dir.z += (ndcx * scale * cam->aspect * cam->right.z) + (ndcy * scale * cam->up.z);
	return (normal(dir));
}
