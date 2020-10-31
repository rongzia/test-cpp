// #include <infiniband/verbs.h>
// #include <cassert>

// struct IBRes {
//     struct ibv_context		*ctx;
//     struct ibv_pd		*pd;
//     struct ibv_mr		*mr;
//     struct ibv_cq		*cq;
//     struct ibv_qp		*qp;
//     struct ibv_port_attr	 port_attr;
//     struct ibv_device_attr	 dev_attr;

//     char   *ib_buf;
//     size_t  ib_buf_size;
// };

// struct IBRes ib_res;

int setup_ib (bool is_server) {
// {
//     int	ret		         = 0;
//     struct ibv_device **dev_list = NULL;    
//     memset (&ib_res, 0, sizeof(struct IBRes));

//     /* get IB device list */
//     dev_list = ibv_get_device_list(NULL);
//     assert(dev_list);

//     /* create IB context */
//     ib_res.ctx = ibv_open_device(*dev_list);
//     assert(ib_res.ctx);

//     /* allocate protection domain */
//     ib_res.pd = ibv_alloc_pd(ib_res.ctx);
//     assert(ib_res.pd);

//     /* query IB port attribute */
//     ret = ibv_query_port(ib_res.ctx, 1, &ib_res.port_attr);
//     assert(0 == ret);
    
//     /* register mr */
//     ib_res.ib_buf_size = 10 * 10;
//     ib_res.ib_buf      = new char[ib_res.ib_buf_size];
//     assert(ib_res.ib_buf);

//     ib_res.mr = ibv_reg_mr (ib_res.pd, (void *)ib_res.ib_buf,
// 			    ib_res.ib_buf_size,
// 			    IBV_ACCESS_LOCAL_WRITE |
// 			    IBV_ACCESS_REMOTE_READ |
// 			    IBV_ACCESS_REMOTE_WRITE);
//     assert(ib_res.mr);
    
//     /* query IB device attr */
//     ret = ibv_query_device(ib_res.ctx, &ib_res.dev_attr);
//     assert(0 == ret);
    
//     /* create cq */
//     ib_res.cq = ibv_create_cq (ib_res.ctx, ib_res.dev_attr.max_cqe, 
// 			       NULL, NULL, 0);
//     assert(ib_res.cq);
    
//     /* create qp */
//     struct ibv_qp_init_attr qp_init_attr = {
//         .send_cq = ib_res.cq,
//         .recv_cq = ib_res.cq,
//         .cap = {
//             .max_send_wr = ib_res.dev_attr.max_qp_wr,
//             .max_recv_wr = ib_res.dev_attr.max_qp_wr,
//             .max_send_sge = 1,
//             .max_recv_sge = 1,
//         },
//         .qp_type = IBV_QPT_RC,
//     };

//     ib_res.qp = ibv_create_qp (ib_res.pd, &qp_init_attr);
//     assert(ib_res.qp);

//     /* connect QP */
//     if (is_server) {
// 	ret = connect_qp_server ();
//     } else {
// 	ret = connect_qp_client ();
//     }
//     assert(0 == ret);

//     ibv_free_device_list (dev_list);
    return 0;
}