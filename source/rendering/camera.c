#include "miniRT.h"

t_vec	generate_cam_dir(t_camera	*cam, double scale, double ndcx, double ndcy)
{
	t_vec	dir;

	dir = cam->forward;
	dir.x += (ndcx * scale * cam->aspect * cam->right.x) + (ndcy * scale * cam->up.x);
	dir.y += (ndcx * scale * cam->aspect * cam->right.y) + (ndcy * scale * cam->up.y);
	dir.z += (ndcx * scale * cam->aspect * cam->right.z) + (ndcy * scale * cam->up.z);
	return (normal(dir));
}
