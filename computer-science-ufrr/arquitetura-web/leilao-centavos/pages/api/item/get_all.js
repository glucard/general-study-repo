import prisma from "../../../lib/prisma";

export default async function getAll(req, res) {

    const result = await prisma.item.findMany({
        include: {
            posted_by: true,
            sold_to: true
        }
    });
    console.log(result);
    res.json(result);

}