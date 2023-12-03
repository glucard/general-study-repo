import prisma from "../../../lib/prisma";

export default async function editItemSoldTo(req, res) {
    
    const { id, sold_to_id, sold_by_amout } = req.body;

    const result = await prisma.item.update({
        where: {
            id: id,
        },
        data: {
            sold_to_id: sold_to_id,
            sold_by_amout, sold_by_amout,
        },
    });
    console.log(result);
    res.json(result);
}