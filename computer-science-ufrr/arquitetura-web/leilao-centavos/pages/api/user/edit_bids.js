import prisma from "../../../lib/prisma";

export default async function editUserBids(req, res) {
    
    const { id, name, email, cpf, password, remain_bids } = req.body;

    const result = await prisma.user.update({
        where: {
            id: id,
        },
        data: {
            remain_bids: remain_bids,
        },
    });
    console.log(result);
    res.json(result);
}